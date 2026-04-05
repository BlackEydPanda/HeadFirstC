#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_scores(const void *score_a, const void *score_b) {
  int a = *(int *)score_a;
  int b = *(int *)score_b;
  return a - b;
}

int compare_scores_desc(const void *score_a, const void *score_b) {
  return compare_scores(score_b, score_a);
}

typedef struct {
  int width;
  int height;
} rectangle;

int compare_areas(const void *a, const void *b) {
  rectangle r_a = *(rectangle *)a;
  rectangle r_b = *(rectangle *)b;

  int area_a = r_a.width * r_b.height;
  int area_b = r_b.width * r_b.height;

  return area_a - area_b;
}

int compare_areas_desc(const void *a, const void *b) {
  return compare_areas(b, a);
}

int compare_names(const void *a, const void *b) {
  char **string_a = (char **)a;
  char **string_b = (char **)b;

  return strcmp(*string_a, *string_b);
}

int compare_names_desc(const void *a, const void *b) {
  return compare_names(b, a);
}

int compare_doubles(const void *a, const void *b) {
  double double_a = *(double *)a;
  double double_b = *(double *)b;

  double diff = double_a - double_b;
  if (diff > 0)
    return 1;
  if (diff < 0)
    return -1;
  return 0;
}

typedef struct {
  int age;
  char *name;
} person;

int compare_persons_by_age(const void *a, const void *b) {
  person person_a = *(person *)a;
  person person_b = *(person *)b;

  return (person_a.age - person_b.age);
}

int compare_persons_by_age_alphabetical_prio(const void *a, const void *b) {
  person person_a = *(person *)a;
  person person_b = *(person *)b;

  int age_gap = person_a.age - person_b.age;
  if (age_gap == 0)
    return compare_names(&person_a.name, &person_b.name);
  return age_gap;
}

typedef struct {
  person student;
  int grade;
} school_test_result;

int compare_by_grade_alphabetical_prio(const void *a, const void *b) {
  school_test_result result_a = *(school_test_result *)a;
  school_test_result result_b = *(school_test_result *)b;

  int grade_diff = result_a.grade - result_b.grade;
  if (grade_diff == 0)
    return compare_names(&result_a.student.name, &result_b.student.name);
  return grade_diff;
}

int main() {
  // int scores[] = {543, 323, 32, 554, 11, 3, 112};
  int i;
  // qsort(scores, 7, sizeof(int), compare_scores_desc);
  // puts("These are the scores in order:");
  // for (i = 0; i < 7; i++) {
  //   printf("Score = %i\n", scores[i]);
  // }
  //
  // char *names[] = {"Karen", "Mark", "Brett", "Molly"};
  // qsort(names, 4, sizeof(char *), compare_names);
  // puts("These are the names in order:");
  // for (i = 0; i < 4; i++) {
  //   printf("%s\n", names[i]);
  // }
  //
  // double doubles[] = {0.1, 0.3, 0.2, -0.1};
  // qsort(doubles, 4, sizeof(double), compare_doubles);
  // puts("these are the doubles in order: ");
  // for (i = 0; i < 4; i++) {
  //   printf("Double = %f\n", doubles[i]);
  // }
  // person persons[] = {{12, "Tom"}, {12, "Ben"}, {25, "Ol'Boi"}, {2, "New
  // Boi"}}; qsort(persons, 4, sizeof(person), compare_persons_by_age);
  // puts("These are the persons sorted by age");
  // for (i = 0; i < 4; i++) {
  //   printf("Name: %s, Age: %i\n", persons[i].name, persons[i].age);
  // }
  //
  // qsort(persons, 4, sizeof(person),
  // compare_persons_by_age_alphabetical_prio); puts("These are the persons
  // sorted by age but alphabetical on ties"); for (i = 0; i < 4; i++) {
  //   printf("Name: %s, Age: %i\n", persons[i].name, persons[i].age);
  // }
  school_test_result results[] = {{{12, "Tom"}, 59},
                                  {{12, "Ben"}, 48},
                                  {{25, "Ol'Boi"}, 48},
                                  {{2, "New Boi"}, 100}};
  qsort(results, 4, sizeof(school_test_result),
        compare_by_grade_alphabetical_prio);
  puts("List of grades sorted with alphabetical prio");
  for (i = 0; i < 4; i++) {
    school_test_result result = results[i];
    printf("Grade: %i, Name: %s\n", result.grade, result.student.name);
  }
  return 0;
}
