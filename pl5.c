#include "pl5.h"

#include <string.h>

#define CCTY(ElementKind) ELEMENT_KIND
#define CCTY(Element) ELEMENT

typedef struct st_null_element {
  ELEMENT_KIND elementKind;
} NullElement;

static NullElement globalNullElement = (NullElement){ EK_NULL };

typedef struct st_int_element {
  ELEMENT_KIND elementKind;
  int64_t value;
} IntElement;

typedef struct st_float_element {
  ELEMENT_KIND elementKind;
  double value;
} FloatElement;

typedef struct st_string_element {
  ELEMENT_KIND elementKind;
  size_t len;
  char buf[0];
} StringElement;

typedef struct st_array_element {
  ELEMENT_KIND elementKind;
  size_t len;
  ELEMENT* elements[0];
} ArrayElement;

typedef struct st_hash_bucket {
  size_t bucketSize;
  size_t bucketUsage;
  ELEMENT elements[0];
} HashBucket;

typedef struct st_object_element {
  ELEMENT_KIND elementKind;
  HashBucket* buckets[512];
} ObjectElement;

typedef struct st_command_element {
  ELEMENT_KIND elementKind;
  char command[255];
  size_t len;
  ELEMENT* args[0];
} CommandElement;

ELEMENT* CCFN(createNullElement)(void) {
  return (ELEMENT*)&globalNullElement;
}

ELEMENT* CCFN(createIntElement)(int64_t value) {
  IntElement *element = malloc(sizeof(IntElement));
  element->elementKind = EK_INT;
  element->value = value;
  return (ELEMENT*)element;
}

ELEMENT* CCFN(createFloatElement)(double value) {
  FloatElement *element = malloc(sizeof(FloatElement));
  element->elementKind = EK_FLOAT;
  element->value = value;
  return (ELEMENT*)element;
}

ELEMENT* CCFN(createStringElement)(const char *value) {
  size_t len = strlen(value);
  StringElement *element = malloc(sizeof(StringElement) + len + 1);
  element->elementKind = EK_STRING;
  element->len = len;
  strcpy(element->buf, value);
}

ELEMENT* CCFN(createArrayElement)(ELEMENT** elements) {
  size_t len = 0;
  for (; elements[len]; ++len);

  ArrayElement *element =
    malloc(sizeof(ArrayElement) + sizeof(ELEMENT*) * len);
  element->elementKind = EK_ARRAY;
  element->len = len;
  for (size_t i = 0; i < len; i++) {
    element->elements[i] = elements[i];
  }
  return (ELEMENT*)element;
}

ELEMENT* CCFN(createObjectElement)(void) {
  ObjectElement *element = malloc(sizeof(ObjectElement));
  element->elementKind = EK_OBJECT;
  memset(element->buckets, 0, sizeof(element->buckets));
  return (ELEMENT*)element;
}

ELEMENT* CCFN(createCommandElement)(const char* command,
                                    ELEMENT** args) {
  
}

