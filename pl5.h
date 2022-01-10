#ifndef PL5_H
#define PL5_H

#include <stddef.h>
#include <stdint.h>

#ifndef CCFN
#define CCFN(x) pl5_##x /* PROC_MACRO_FALLBACK */
#endif /* CCFN */

#ifndef CCTY
#define CCTY(x) pl5_##x /* PROC_MACRO_FALLBACK */
#endif /* CCTY */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum e_pl5_element_kind {
  EK_NULL,
  EK_INT,
  EK_FLOAT,
  EK_STRING,
  EK_ARRAY,
  EK_OBJECT,
  EK_COMMAND
} CCTY(ElementKind);

typedef struct st_pl5_element_base {
} CCTY(Element);

CCTY(Element)* CCFN(createNullElement)(void);
CCTY(Element)* CCFN(createIntElement)(int64_t);
CCTY(Element)* CCFN(createFloatElement)(double);
CCTY(Element)* CCFN(createStringElement)(const char*);
CCTY(Element)* CCFN(createArrayElement)(CCTY(Element)**);
CCTY(Element)* CCFN(createObjectElement)(void);
CCTY(Element)* CCFN(createCommandElement)(const char*, CCTY(Element)**);

CCTY(ElementKind) CCFN(elementKind)(const CCTY(Element)*);
_Bool CCFN(elementIsNull)(const CCTY(Element)*);
_Bool CCFN(elementIsNumber)(const CCTY(Element)*);
_Bool CCFN(elementIsInt)(const CCTY(Element)*);
_Bool CCFN(elementIsFloat)(const CCTY(Element)*);
_Bool CCFN(elementIsString)(const CCTY(Element)*);
_Bool CCFN(elementIsArray)(const CCTY(Element)*);
_Bool CCFN(elementIsObject)(const CCTY(Element)*);
_Bool CCFN(elementIsCommand)(const CCTY(Element)*);

int64_t CCFN(elementAsInt)(const CCTY(Element)*);
double CCFN(elementAsFloat)(const CCTY(Element)*);
const char* CCFN(elementAsString)(const CCTY(Element)*);
size_t CCFN(elementArrLen)(const CCTY(Element)*);
const CCTY(Element)* CCFN(elementArrGet)(const CCTY(Element)*, size_t);
CCTY(Element)* CCFN(elementArrGetMut)(CCTY(Element)*, size_t);
const CCTY(Element)* CCFN(elementObjGet)(const CCTY(Element)*,
                                         const char*);
CCTY(Element)* CCFN(elementObjGetMut)(CCTY(Element)*, const char*);
void CCFN(deleteElement)(CCTY(Element)*);

CCTY(Element)* CCFN(parseElement)(const char*);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PL5_H */

