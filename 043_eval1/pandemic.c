#include "pandemic.h"

country_t parseLine(char * line) {
  if (line == NULL) {
    fprintf(stderr, "Error: unexpected passing NULL to parseLine\n");
    exit(EXIT_FAILURE);
  }
  //WRITE ME
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;

  // seperate the country name and population, and it also chcek the format of string
  char * countryNamePtr = strtok(
      line,
      ",");  // this would change the first , to /0, but still return first characters in line
  char * populationPtr = strtok(NULL, ",");
  if (populationPtr == NULL) {
    fprintf(stderr, "Error: wrong format for population\n");
    exit(EXIT_FAILURE);
  }
  size_t countryNameSize = populationPtr - countryNamePtr;
  // safe copy country Name
  if (countryNameSize > MAX_NAME_LEN) {
    fprintf(stderr,
            "Error: country name exceed max country name size: 64, country name size is "
            "%zu\n",
            countryNameSize);
    exit(EXIT_FAILURE);
  }
  strncpy(ans.name, countryNamePtr, countryNameSize);

  // assign population valu
  if ((ans.population = strtol(populationPtr, NULL, 10)) == LONG_MAX) {
    fprintf(stderr, "Error: population overflow or get negative value\n");
    exit(EXIT_FAILURE);
  }

  // prevent format as [country], population, ..., ....
  if (strtok(NULL, ",") != NULL) {
    fprintf(stderr,
            "Error: incorrect format with population (it must have [country_name], "
            "[population])\n");
    exit(EXIT_FAILURE);
  }

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  if (n_days <= 0)
    return;
  //WRITE ME
  if (data == NULL || avg == NULL) {
    fprintf(stderr, "Error: passing NULL\n");
    exit(EXIT_FAILURE);
  }

  size_t i = 0, j = 0;
  double sum = 0;
  for (i = 0; i < n_days - 6; i++) {
    sum = 0;
    for (j = i; j < i + 7; j++) {
      // check exceed allowed memory area
      if (data + j == NULL) {
        fprintf(stderr, "Error: calcRunningavg exceed leagal memory area\n");
        exit(EXIT_FAILURE);
      }
      // check overflow
      if (sum + *(data + j) < sum) {
        fprintf(stderr, "Error: overflow happen in sum\n");
        exit(EXIT_FAILURE);
      }
      sum += *(data + j);
    }

    if (avg + i == NULL) {
      fprintf(stderr, "Error: calcRunningavg exceed leagal memory area\n");
      exit(EXIT_FAILURE);
    }
    avg[i] = sum / 7;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  if (n_days <= 0)
    return;

  if (data == NULL || cum == NULL) {
    fprintf(stderr, "Error: NULL pointer passed in\n");
    exit(EXIT_FAILURE);
  }

  //WRITE ME
  size_t i = 0;
  double sum = 0.0;
  for (i = 0; i < n_days; i++) {
    if (data + i == NULL || cum + i == NULL) {
      fprintf(stderr, "Error: calcCumulative attemps to access invalid memory\n");
      exit(EXIT_FAILURE);
    }
    sum += data[i];
    cum[i] = (sum / pop) * 100000;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  if (n_countries <= 0 || n_days <= 0)
    return;

  if (countries == NULL || data == NULL) {
    fprintf(stderr, "Error: passing null to countries or data is not allowed\n");
    exit(EXIT_FAILURE);
  }

  // test the number of countries in country_t* is not smaller than size_t n_countries
  size_t idx = 0;
  for (idx = 0; idx < n_countries; idx++) {
    if (countries + idx == NULL) {
      fprintf(
          stderr,
          "Error: potential acessing invalid memory in function printCountryWithMax\n");
      exit(EXIT_FAILURE);
    }
  }

  for (size_t i = 0; i < n_countries; i++) {
    unsigned * mvptr = data[i];
    if (mvptr == NULL) {
      fprintf(stderr, "Error: invalid memory\n");
      exit(EXIT_FAILURE);
    }

    for (size_t j = 0; j < n_days; j++) {
      if (mvptr == NULL) {
        fprintf(stderr, "Error: invalid memory\n");
        exit(EXIT_FAILURE);
      }
      mvptr++;
    }
  }

  //Valid Data Handle
  size_t i = 0, j = 0, maxCountryId = 0;
  unsigned max = 0;
  // use row-based to increase performance, since this correponding to the mechanism of cache localization
  for (i = 0; i < n_countries; i++) {
    for (j = 0; j < n_days; j++) {
      if (data[i][j] > max) {
        maxCountryId = i;
        max = data[i][j];
      }

      else if (data[i][j] == max && i != maxCountryId) {
        printf("There is a tie between at least two countries\n");
        return;
      }
    }
  }

  if (maxCountryId >= n_countries) {
    fprintf(stderr, "Error: unexpected error occur\n");
    exit(EXIT_FAILURE);
  }

  printf("%s has the most daily cases with %u\n", countries[maxCountryId].name, max);
}
