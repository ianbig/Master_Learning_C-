#include "./rand_story.h"

void init_track(category_t * track) {
  track->name = NULL;
  track->words = NULL;
  track->n_words = 0;
}

void addTrack(category_t * track, const char * words) {
  track->n_words += 1;
  size_t newIndex = track->n_words - 1;
  if ((track->words = realloc(track->words, sizeof(*track->words) * track->n_words)) ==
      NULL) {
    fprintf(stderr, "realloc error in addTrack\n");
    exit(EXIT_FAILURE);
  }

  if ((track->words[newIndex] =
           malloc(sizeof(*track->words[newIndex]) * (strlen(words) + 1))) == NULL) {
    fprintf(stderr, "realloc error in addTrack\n");
    exit(EXIT_FAILURE);
  }
  strncpy(track->words[newIndex], words, strlen(words));
  track->words[newIndex][strlen(words)] = '\0';
}

void printTrack(category_t * track) {
  for (size_t i = 0; i < track->n_words; i++) {
    printf("tracking index %lu is %s\n", i, track->words[i]);
  }
}

char * pickWRef(const char * cat, category_t * track) {
  size_t ref = strtol(cat, NULL, 0);
  if (ref == LONG_MAX) {
    fprintf(stderr, "pickWRef: overflow occur\n");
    exit(EXIT_FAILURE);
  }
  if (ref > track->n_words || ref <= 0) {
    fprintf(stderr,
            "pickWRef: reference number is bigger than existing tracking words or "
            "smaller than 0\n");
    exit(EXIT_FAILURE);
  }

  return track->words[track->n_words - ref];
}

void freeTrack(category_t * track) {
  for (size_t i = 0; i < track->n_words; i++) {
    free(track->words[i]);
  }
  free(track->words);
}

void deleteWords(category_t * cat, const char * words) {
  assert(cat != NULL && words != NULL);
  size_t del_index = 0, i = 0;
  // locate words
  for (i = 0; i < cat->n_words; i++) {
    if (strcmp(cat->words[i], words) == 0) {
      del_index = i;
      break;
    }
  }
  assert(i != cat->n_words);
  // printf("%s is deleted\n", cat->words[i]);
  // delete words
  free(cat->words[i]);
  for (i = del_index; i < cat->n_words - 1; i++) {
    cat->words[i] = cat->words[i + 1];
  }
  cat->n_words--;
}
// TODO: refactors this fuction to have more abstraction
char * parseLine(char ** parsed,
                 char * mvptr,
                 size_t * sz,
                 catarray_t * cats,
                 category_t * track,
                 int n_opt) {
  char *first = NULL, *second = NULL, *category = NULL, *parsed_end = NULL;
  size_t newSz = 0;

  parsed_end = *parsed + *sz;
  // find the first "_"
  while ((first = strstr(mvptr, "_")) != NULL) {
    second = strstr(first + 1, "_");
    // if unable to locate second "_", meaning the format is problematic
    if (second == NULL) {
      fprintf(stderr, "parseFile: wrong format for category");
      exit(EXIT_FAILURE);
    }

    // ensure the category name not exceed memory
    if ((category = malloc((second - first) * sizeof(*category))) == NULL) {
      fprintf(stderr, "parseFile: realloc fail");
      exit(EXIT_FAILURE);
    }

    // choose words according to category
    const char * words = NULL;
    char * endptr = NULL;
    strncpy(category, first + 1, second - first - 1);
    category[second - first - 1] = '\0';
    strtol(category, &endptr, 0);
    if (*endptr == '\0') {
      words = pickWRef(category, track);
    }
    else {
      words = chooseWord(category, cats);
    }
    addTrack(track, words);

    // copy changed words to buffer
    newSz = first - mvptr + *sz + strlen(words);
    if ((*parsed = realloc(*parsed, newSz * sizeof(**parsed))) == NULL) {
      fprintf(stderr, "parseFile: realloc fail");
      exit(EXIT_FAILURE);
    }

    parsed_end = *parsed + *sz;  // move the end of original parsed
    strncpy(parsed_end, mvptr, first - mvptr);
    parsed_end += first - mvptr;
    // copy new words to template
    strncpy(parsed_end, words, strlen(words));
    parsed_end += strlen(words);
    // delte words from category if -n option
    if (n_opt == 1 && *endptr != '\0') {
      category_t * findCate = findCat(category, cats);
      deleteWords(findCate, words);
    }
    free(category);
    // moving pointer for searching next blank
    mvptr = second + 1;
    *sz = newSz;
  }

  // copy the rest char to buffer
  if ((*parsed = realloc(*parsed, sizeof(*parsed) * (*sz + strlen(mvptr) + 1))) == NULL) {
    fprintf(stderr, "parseFile: realloc fail");
    exit(EXIT_FAILURE);
  }
  parsed_end = *parsed + *sz;  // move to the original end
  *sz += strlen(mvptr);
  strncpy(parsed_end, mvptr, strlen(mvptr));
  parsed_end += strlen(mvptr);

  return parsed_end;
}

char * parseFile(const char * fileName, catarray_t * cats, int n_opt) {
  // open the file
  FILE * fp = fopen(fileName, "r");
  if (fp == NULL) {
    fprintf(stderr, "parseFile: file cannot open\n");
    exit(EXIT_FAILURE);
  }

  char * lineptr = NULL;
  size_t sz = 0, parse_len = 0;
  char *parsed = NULL, *end = NULL;
  category_t track;
  init_track(&track);
  // parse file
  while (getline(&lineptr, &sz, fp) != -1) {
    end = parseLine(&parsed, lineptr, &parse_len, cats, &track, n_opt);
  }
  *end = '\0';

  freeTrack(&track);
  free(lineptr);
  fclose(fp);
  return parsed;
}

void init_cats(catarray_t * cats) {
  assert(cats != NULL);
  cats->arr = NULL;
  cats->n = 0;
}

// TODO: not using so much malloc and free to improve performance
void divideKeyWords(char * lineptr, char ** key, char ** words) {
  char * del = strstr(lineptr, ":");
  if (del == NULL) {
    fprintf(stderr, "Error: wrong format\n");
    exit(EXIT_FAILURE);
  }

  if ((*key = malloc(sizeof(**key) * (del - lineptr + 1))) == NULL) {
    fprintf(stderr, "Error in realloc in divideKeyWords\n");
    exit(EXIT_FAILURE);
  }
  strncpy(*key, lineptr, del - lineptr);
  (*key)[del - lineptr] = '\0';

  char * wordsEnd = strstr(del, "\n");
  if ((*words = malloc(sizeof(**words) * (wordsEnd - del))) == NULL) {
    fprintf(stderr, "Error in realloc in divideKeyWords\n");
    exit(EXIT_FAILURE);
  }
  strncpy(*words, del + 1, wordsEnd - del);
  (*words)[wordsEnd - del - 1] = '\0';
}

category_t * findCat(char * key, catarray_t * cats) {
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp(cats->arr[i].name, key) == 0) {
      return &cats->arr[i];
    }
  }

  return NULL;
}

category_t * addNewCat(catarray_t * cats, const char * key) {
  cats->n += 1;
  if ((cats->arr = realloc(cats->arr, sizeof(*cats->arr) * cats->n)) == NULL) {
    fprintf(stderr, "Error in realloc in addNewCat\n");
    exit(EXIT_FAILURE);
  }

  // initailize new category
  cats->arr[cats->n - 1].name =
      malloc(sizeof(cats->arr[cats->n]) * strlen(key) + 1);    // include \0
  strncpy(cats->arr[cats->n - 1].name, key, strlen(key) + 1);  // include \0
  cats->arr[cats->n - 1].words = NULL;
  cats->arr[cats->n - 1].n_words = 0;

  return &cats->arr[cats->n - 1];
}

void addWordToCat(category_t * cat, const char * words) {
  // add n_words
  cat->n_words += 1;
  // realloc new memory to fetched category
  if ((cat->words = realloc(cat->words, sizeof(*cat->words) * cat->n_words)) == NULL) {
    fprintf(stderr, "realloc error in addWordtoCat\n");
    exit(EXIT_FAILURE);
  }
  // allocate new memory for *words
  if ((cat->words[cat->n_words - 1] =
           malloc(sizeof(*cat->words[cat->n_words]) * (strlen(words) + 1))) == NULL) {
    fprintf(stderr, "realloc error in addWordtoCat\n");
    exit(EXIT_FAILURE);
  }
  // copy words to to cat.words
  strncpy(cat->words[cat->n_words - 1], words, strlen(words));
  cat->words[cat->n_words - 1][strlen(words)] = '\0';
}

void printAddNewCats(catarray_t * cats) {
  for (size_t i = 0; i < cats->n; i++) {
    printf("cat %s with  n_words %lu\n", cats->arr[i].name, cats->arr[i].n_words);
  }
}

catarray_t * parseCats(const char * filename, int debug) {
  FILE * fp = fopen(filename, "r");
  if (fp == NULL) {
    fprintf(stderr, "Error:  %s cannot open\n", filename);
    exit(EXIT_FAILURE);
  }
  // malloc a memory for catarray_t
  catarray_t * cats = malloc(sizeof(*cats));
  if (cats == NULL) {
    fprintf(stderr, "Error: parseCats unable to allocate memory\n");
    exit(EXIT_FAILURE);
  }
  init_cats(cats);

  category_t * cat = NULL;
  char *lineptr = NULL, *key = NULL, *words = NULL;
  size_t sz = 0;
  while (getline(&lineptr, &sz, fp) != -1) {
    // divide the key and wors
    divideKeyWords(lineptr, &key, &words);
    // find corresponding category
    cat = findCat(key, cats);
    if (cat == NULL) {
      cat = addNewCat(cats, key);
    }
    // add word to category
    addWordToCat(cat, words);
    free(words);
    free(key);
  }

  if (debug == 1) {
    printWords(cats);
  }

  free(lineptr);
  fclose(fp);

  return cats;
}

void freeCats(catarray_t * cats) {
  for (size_t i = 0; i < cats->n; i++) {
    free(cats->arr[i].name);
    for (size_t j = 0; j < cats->arr[i].n_words; j++) {
      free(cats->arr[i].words[j]);
    }
    free(cats->arr[i].words);
  }

  free(cats->arr);
  free(cats);
}
