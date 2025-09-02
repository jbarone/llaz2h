#include "common.h"
#include "parse.h"
#include <stdlib.h>
#include <unity/unity.h>

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_function_should_create_db_header(void) {
  struct dbheader_t *header = NULL;
  if (create_db_header(&header) == STATUS_ERROR) {
    TEST_FAIL_MESSAGE("unable to create db header");
  }
  TEST_ASSERT_NOT_NULL(header);
  TEST_ASSERT_EQUAL_UINT32(1, header->version);
  free(header);
}

void test_function_should_list_employees_memory(void) {
  struct dbheader_t *dbhdr = NULL;
  struct employee_t *employees = NULL;
  if (create_db_header(&dbhdr) == STATUS_ERROR) {
    TEST_FAIL_MESSAGE("unable to create db header");
  }

  if (add_employee(dbhdr, &employees, "John Doe,123 Main St,40") ==
      STATUS_ERROR) {
    free(dbhdr);
    TEST_FAIL_MESSAGE("unable to add employee");
  }

  list_employees(dbhdr, employees); // Should handle NULL employees gracefully

  free(employees);
  free(dbhdr);
}

void test_function_should_not_crash_list_employees_null(void) {
  struct dbheader_t *dbhdr = NULL;
  struct employee_t *employees = NULL;
  if (create_db_header(&dbhdr) == STATUS_ERROR) {
    TEST_FAIL_MESSAGE("unable to create db header");
  }

  list_employees(dbhdr, employees); // Should handle NULL employees gracefully

  free(employees);
  free(dbhdr);
}

void test_function_should_not_crash_list_employees_null_header(void) {
  struct dbheader_t *dbhdr = NULL;
  struct employee_t *employees = NULL;
  if (create_db_header(&dbhdr) == STATUS_ERROR) {
    TEST_FAIL_MESSAGE("unable to create db header");
  }

  if (add_employee(dbhdr, &employees, "John Doe,123 Main St,40") ==
      STATUS_ERROR) {
    free(dbhdr);
    TEST_FAIL_MESSAGE("unable to add employee");
  }

  list_employees(NULL, employees); // Should handle NULL employees gracefully

  free(employees);
  free(dbhdr);
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_function_should_create_db_header);
  RUN_TEST(test_function_should_list_employees_memory);
  RUN_TEST(test_function_should_not_crash_list_employees_null);
  RUN_TEST(test_function_should_not_crash_list_employees_null_header);
  return UNITY_END();
}
