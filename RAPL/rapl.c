
/*
 *  João De Macedo
 *  2021
 */

#include "rapl.h"

int cpu_model;
int core = 0;

double package_before, package_after;
double pp0_before, pp0_after;
double pp1_before = 0.0, pp1_after;
double dram_before = 0.0, dram_after;

double power_units, energy_units, time_units;

int dram_avail = 0, pp0_avail = 0, pp1_avail = 0, psys_avail = 0; //
int different_units = 0; //

int open_msr(int core)
{

  char msr_filename[BUFSIZ];
  int fd;

  sprintf(msr_filename, "/dev/cpu/%d/msr", core);
  fd = open(msr_filename, O_RDONLY);
  if (fd < 0)
  {
    if (errno == ENXIO)
    {
      fprintf(stderr, "rdmsr: No CPU %d\n", core);
      exit(2);
    }
    else if (errno == EIO)
    {
      fprintf(stderr, "rdmsr: CPU %d doesn't support MSRs\n", core);
      exit(3);
    }
    else
    {
      perror("rdmsr:open");
      fprintf(stderr, "Trying to open %s\n", msr_filename);
      exit(127);
    }
  }

  return fd;
}

long long read_msr(int fd, int which)
{

  uint64_t data;

  if (pread(fd, &data, sizeof data, which) != sizeof data)
  {
    perror("rdmsr:pread");
    exit(127);
  }

  return (long long)data;
}

#define CPU_SANDYBRIDGE 42
#define CPU_SANDYBRIDGE_EP 45
#define CPU_IVYBRIDGE 58
#define CPU_IVYBRIDGE_EP 62
#define CPU_HASWELL 60
#define CPU_HASWELL_ULT 69       //
#define CPU_HASWELL_GT3E 70      //
#define CPU_HASWELL_EP 63        //
#define CPU_BROADWELL 61         //
#define CPU_BROADWELL_GT3E 71    //
#define CPU_BROADWELL_EP 79      //
#define CPU_BROADWELL_DE 86      //
#define CPU_SKYLAKE 78           //
#define CPU_SKYLAKE_HS 94        //
#define CPU_SKYLAKE_X 85         //
#define CPU_KNIGHTS_LANDING 87   //
#define CPU_KNIGHTS_MILL 133     //
#define CPU_KABYLAKE_MOBILE 142  //
#define CPU_KABYLAKE 158         //
#define CPU_ATOM_SILVERMONT 55   //
#define CPU_ATOM_AIRMONT 76      //
#define CPU_ATOM_MERRIFIELD 74   //
#define CPU_ATOM_MOOREFIELD 90   //
#define CPU_ATOM_GOLDMONT 92     //
#define CPU_ATOM_GEMINI_LAKE 122 //
#define CPU_ATOM_DENVERTON 95    //

/* TODO: on Skylake, also may support  PSys "platform" domain,	*/ //
/* the whole SoC not just the package.				*/                   //
/* see dcee75b3b7f025cc6765e6c92ba0a4e59a4d25f4			*/             //

int detect_cpu(void)
{

  FILE *fff;

  int family, model = -1;
  char buffer[BUFSIZ], *result;
  char vendor[BUFSIZ];

  fff = fopen("/proc/cpuinfo", "r");
  if (fff == NULL)
    return -1;

  while (1)
  {
    result = fgets(buffer, BUFSIZ, fff);
    if (result == NULL)
      break;

    if (!strncmp(result, "vendor_id", 8))
    {
      sscanf(result, "%*s%*s%s", vendor);

      if (strncmp(vendor, "GenuineIntel", 12))
      {
        printf("%s not an Intel chip\n", vendor);
        return -1;
      }
    }

    if (!strncmp(result, "cpu family", 10))
    {
      sscanf(result, "%*s%*s%*s%d", &family);
      if (family != 6)
      {
        printf("Wrong CPU family %d\n", family);
        return -1;
      }
    }

    if (!strncmp(result, "model", 5))
    {
      sscanf(result, "%*s%*s%d", &model);
    }
  }

  fclose(fff);

  printf("Found "); //

  switch (model)
  {
  case CPU_SANDYBRIDGE:
    printf("Sandybridge");
    break;
  case CPU_SANDYBRIDGE_EP:
    printf("Sandybridge-EP");
    break;
  case CPU_IVYBRIDGE:
    printf("Ivybridge");
    break;
  case CPU_IVYBRIDGE_EP:
    printf("Ivybridge-EP");
    break;
  case CPU_HASWELL:
  case CPU_HASWELL_ULT:
  case CPU_HASWELL_GT3E:
    printf("Haswell");
    break;
  case CPU_HASWELL_EP:
    printf("Haswell-EP");
    break;
  case CPU_BROADWELL:
  case CPU_BROADWELL_GT3E:
    printf("Broadwell");
    break;
  case CPU_BROADWELL_EP:
    printf("Broadwell-EP");
    break;
  case CPU_SKYLAKE:
  case CPU_SKYLAKE_HS:
    printf("Skylake");
    break;
  case CPU_SKYLAKE_X:
    printf("Skylake-X");
    break;
  case CPU_KABYLAKE:
  case CPU_KABYLAKE_MOBILE:
    printf("Kaby Lake");
    break;
  case CPU_KNIGHTS_LANDING:
    printf("Knight's Landing");
    break;
  case CPU_KNIGHTS_MILL:
    printf("Knight's Mill");
    break;
  case CPU_ATOM_GOLDMONT:
  case CPU_ATOM_GEMINI_LAKE:
  case CPU_ATOM_DENVERTON:
    printf("Atom");
    break;
  default:
    printf("Unsupported model %d\n", model);
    model = -1;
    break;
  }

  printf(" Processor type\n");

  return model;
}

#define MAX_CPUS 1024 //
#define MAX_PACKAGES 16 //

int rapl_init(int core)
{
  int fd;
  long long result;

  cpu_model = detect_cpu();
  if (cpu_model < 0)
  {
    printf("\tUnsupported CPU model %d\n", cpu_model);
    return -1;
  }

  switch (cpu_model)
	{

	case CPU_SANDYBRIDGE_EP:
	case CPU_IVYBRIDGE_EP:
		pp0_avail = 1;
		pp1_avail = 0;
		dram_avail = 1;
		different_units = 0;
		psys_avail = 0;
		break;

	case CPU_HASWELL_EP:
	case CPU_BROADWELL_EP:
	case CPU_SKYLAKE_X:
		pp0_avail = 1;
		pp1_avail = 0;
		dram_avail = 1;
		different_units = 1;
		psys_avail = 0;
		break;

	case CPU_KNIGHTS_LANDING:
	case CPU_KNIGHTS_MILL:
		pp0_avail = 0;
		pp1_avail = 0;
		dram_avail = 1;
		different_units = 1;
		psys_avail = 0;
		break;

	case CPU_SANDYBRIDGE:
	case CPU_IVYBRIDGE:
		pp0_avail = 1;
		pp1_avail = 1;
		dram_avail = 0;
		different_units = 0;
		psys_avail = 0;
		break;

	case CPU_HASWELL:
	case CPU_HASWELL_ULT:
	case CPU_HASWELL_GT3E:
	case CPU_BROADWELL:
	case CPU_BROADWELL_GT3E:
	case CPU_ATOM_GOLDMONT:
	case CPU_ATOM_GEMINI_LAKE:
	case CPU_ATOM_DENVERTON:
		pp0_avail = 1;
		pp1_avail = 1;
		dram_avail = 1;
		different_units = 0;
		psys_avail = 0;
		break;

	case CPU_SKYLAKE:
	case CPU_SKYLAKE_HS:
	case CPU_KABYLAKE:
	case CPU_KABYLAKE_MOBILE:
		pp0_avail = 1;
		pp1_avail = 1;
		dram_avail = 1;
		different_units = 0;
		psys_avail = 1;
		break;
	}

  // printf("Checking core #%d\n",core);

  fd = open_msr(core);

  /* Calculate the units used */
  result = read_msr(fd, MSR_RAPL_POWER_UNIT);

  power_units = pow(0.5, (double)(result & 0xf));
  energy_units = pow(0.5, (double)((result >> 8) & 0x1f));
  time_units = pow(0.5, (double)((result >> 16) & 0xf));

  /*
  printf("Power units = %.3fW\n",power_units);
  printf("Energy units = %.8fJ\n",energy_units);
  printf("Time units = %.8fs\n",time_units);
  printf("\n");
  */

  return 0;
}

void show_power_info(int core)
{
  int fd;
  long long result;
  double thermal_spec_power, minimum_power, maximum_power, time_window;

  /* Show package power info */

  fd = open_msr(core);
  result = read_msr(fd, MSR_PKG_POWER_INFO);

  thermal_spec_power = power_units * (double)(result & 0x7fff);
  printf("Package thermal spec: %.3fW\n", thermal_spec_power);

  minimum_power = power_units * (double)((result >> 16) & 0x7fff);
  printf("Package minimum power: %.3fW\n", minimum_power);

  maximum_power = power_units * (double)((result >> 32) & 0x7fff);
  printf("Package maximum power: %.3fW\n", maximum_power);

  time_window = time_units * (double)((result >> 48) & 0x7fff);
  printf("Package maximum time window: %.6fs\n", time_window);
}

void show_power_limit(int core)
{
  int fd;
  long long result;

  /* Show package power limit */

  fd = open_msr(core);
  result = read_msr(fd, MSR_PKG_RAPL_POWER_LIMIT);

  printf("Package power limits are %s\n", (result >> 63) ? "locked" : "unlocked");
  double pkg_power_limit_1 = power_units * (double)((result >> 0) & 0x7FFF);
  double pkg_time_window_1 = time_units * (double)((result >> 17) & 0x007F);
  printf("Package power limit #1: %.3fW for %.6fs (%s, %s)\n", pkg_power_limit_1, pkg_time_window_1,
         (result & (1LL << 15)) ? "enabled" : "disabled",
         (result & (1LL << 16)) ? "clamped" : "not_clamped");
  double pkg_power_limit_2 = power_units * (double)((result >> 32) & 0x7FFF);
  double pkg_time_window_2 = time_units * (double)((result >> 49) & 0x007F);
  printf("Package power limit #2: %.3fW for %.6fs (%s, %s)\n", pkg_power_limit_2, pkg_time_window_2,
         (result & (1LL << 47)) ? "enabled" : "disabled",
         (result & (1LL << 48)) ? "clamped" : "not_clamped");

  printf("\n");
}

void rapl_before(FILE *fp, int core)
{
  int fd;
  long long result;

  fd = open_msr(core);
  result = read_msr(fd, MSR_PKG_ENERGY_STATUS);

  package_before = (double)result * energy_units;
  //  fprintf(fp,"Package energy: %.6fJ\n",package_before);

  /* only available on *Bridge-EP */
  if ((cpu_model == CPU_SANDYBRIDGE_EP) || (cpu_model == CPU_IVYBRIDGE_EP))
  {
    result = read_msr(fd, MSR_PKG_PERF_STATUS);
    double acc_pkg_throttled_time = (double)result * time_units;
    // fprintf(fp,"Accumulated Package Throttled Time : %.6fs\n",acc_pkg_throttled_time);
  }

  result = read_msr(fd, MSR_PP0_ENERGY_STATUS);
  pp0_before = (double)result * energy_units;
  // fprintf(fp,"PowerPlane0 (core) for core %d energy before: %.6fJ\n",core,pp0_before);

  result = read_msr(fd, MSR_PP0_POLICY);
  int pp0_policy = (int)result & 0x001f;
  // fprintf(fp,"PowerPlane0 (core) for core %d policy: %d\n",core,pp0_policy);

  /* only available on *Bridge-EP */
  if ((cpu_model == CPU_SANDYBRIDGE_EP) || (cpu_model == CPU_IVYBRIDGE_EP))
  {
    result = read_msr(fd, MSR_PP0_PERF_STATUS);
    double acc_pp0_throttled_time = (double)result * time_units;
    // fprintf(fp,"PowerPlane0 (core) Accumulated Throttled Time : %.6fs\n",acc_pp0_throttled_time);
  }

  /* not available on *Bridge-EP */
  if (pp1_avail)
  {
    result = read_msr(fd, MSR_PP1_ENERGY_STATUS);
    pp1_before = (double)result * energy_units;
    // fprintf(fp,"PowerPlane1 (on-core GPU if avail) before: %.6fJ\n",pp1_before);
    result = read_msr(fd, MSR_PP1_POLICY);
    int pp1_policy = (int)result & 0x001f;
    //fprintf(fp,"PowerPlane1 (on-core GPU if avail) %d policy: %d\n",core,pp1_policy);
  }

  /* Despite documentation saying otherwise, it looks like */
  /* You can get DRAM readings on regular Haswell          */
  if (dram_avail)
  {
    result = read_msr(fd, MSR_DRAM_ENERGY_STATUS);
    dram_before = (double)result * energy_units;
    // fprintf(fp,"DRAM energy before: %.6fJ\n",dram_before);
  }

  close(fd);
}

void rapl_after(FILE *fp, int core)
{
  int fd;
  long long result;

  fd = open_msr(core);

  result = read_msr(fd, MSR_PKG_ENERGY_STATUS);
  package_after = (double)result * energy_units;
  //  fprintf(fp,"Package energy: %.6fJ consumed\n",package_after-package_before);
  fprintf(fp, "%.6f , ", package_after - package_before); // PACKAGE

  result = read_msr(fd, MSR_PP0_ENERGY_STATUS);
  pp0_after = (double)result * energy_units;

  fprintf(fp, "%.6f , ", pp0_after - pp0_before); // CORE

  /* not available on SandyBridge-EP */
  if (pp1_avail)
  {
    result = read_msr(fd, MSR_PP1_ENERGY_STATUS);
    pp1_after = (double)result * energy_units;
    fprintf(fp, "%.6f , ", pp1_after - pp1_before); // GPU
  }
  else
    fprintf(fp, "  , ");

  if (dram_avail)
  {
    result = read_msr(fd, MSR_DRAM_ENERGY_STATUS);
    dram_after = (double)result * energy_units;
    fprintf(fp, "%.6f \n", dram_after - dram_before); // DRAM
  }
  else
    fprintf(fp, "  \n");

  close(fd);
}
