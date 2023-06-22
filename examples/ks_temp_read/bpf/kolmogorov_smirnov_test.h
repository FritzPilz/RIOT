#ifndef KS_TEST
#define KS_TEST

#include "bpf.h"
#include "bpf/shared.h"

#define RANGE 1024
#define STEP 64
#define STEPS 16

typedef struct benchmark_runs{
    uint32_t times_to_run;
    uint32_t time_taken_in_usec;
} benchmark_runs;

typedef struct KS_Test_State{
    __bpf_shared_ptr(int32_t *, expectedFunction);
    __bpf_shared_ptr(int32_t *, empiricalFunction);
    NRF_TEMP_Type* temp_sensor;
    uint32_t value;
    uint32_t result;
} KS_Test_State;

typedef struct {
    __bpf_shared_ptr(KS_Test_State *, kolmogorov_ctx);
} kolmogorov_ctx_t;

uint32_t delta_kolmogorov_smirnov_test(kolmogorov_ctx_t* ctx);

void create_function(void);

void printList(int32_t* arr1, int32_t* arr2);

void runTest(bpf_t* ks_bpf, kolmogorov_ctx_t* ctx, benchmark_runs* test);

int32_t expectedFunction[16];
int32_t empiricalFunction[16];

#ifndef NRF52833_H
#define NRF52833_H

#define   __I     volatile const       /*!< Defines 'read only' permissions */
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

typedef struct {                                /*!< (@ 0x4000C000) TEMP Structure                                             */
  __OM  uint32_t  TASKS_START;                  /*!< (@ 0x00000000) Start temperature measurement                              */
  __OM  uint32_t  TASKS_STOP;                   /*!< (@ 0x00000004) Stop temperature measurement                               */
  __IM  uint32_t  RESERVED[62];
  __IOM uint32_t  EVENTS_DATARDY;               /*!< (@ 0x00000100) Temperature measurement complete, data ready               */
  __IM  uint32_t  RESERVED1[128];
  __IOM uint32_t  INTENSET;                     /*!< (@ 0x00000304) Enable interrupt                                           */
  __IOM uint32_t  INTENCLR;                     /*!< (@ 0x00000308) Disable interrupt                                          */
  __IM  uint32_t  RESERVED2[127];
  __IM  int32_t   TEMP;                         /*!< (@ 0x00000508) Temperature in degC (0.25deg steps)                        */
  __IM  uint32_t  RESERVED3[5];
  __IOM uint32_t  A0;                           /*!< (@ 0x00000520) Slope of 1st piece wise linear function                    */
  __IOM uint32_t  A1;                           /*!< (@ 0x00000524) Slope of 2nd piece wise linear function                    */
  __IOM uint32_t  A2;                           /*!< (@ 0x00000528) Slope of 3rd piece wise linear function                    */
  __IOM uint32_t  A3;                           /*!< (@ 0x0000052C) Slope of 4th piece wise linear function                    */
  __IOM uint32_t  A4;                           /*!< (@ 0x00000530) Slope of 5th piece wise linear function                    */
  __IOM uint32_t  A5;                           /*!< (@ 0x00000534) Slope of 6th piece wise linear function                    */
  __IM  uint32_t  RESERVED4[2];
  __IOM uint32_t  B0;                           /*!< (@ 0x00000540) y-intercept of 1st piece wise linear function              */
  __IOM uint32_t  B1;                           /*!< (@ 0x00000544) y-intercept of 2nd piece wise linear function              */
  __IOM uint32_t  B2;                           /*!< (@ 0x00000548) y-intercept of 3rd piece wise linear function              */
  __IOM uint32_t  B3;                           /*!< (@ 0x0000054C) y-intercept of 4th piece wise linear function              */
  __IOM uint32_t  B4;                           /*!< (@ 0x00000550) y-intercept of 5th piece wise linear function              */
  __IOM uint32_t  B5;                           /*!< (@ 0x00000554) y-intercept of 6th piece wise linear function              */
  __IM  uint32_t  RESERVED5[2];
  __IOM uint32_t  T0;                           /*!< (@ 0x00000560) End point of 1st piece wise linear function                */
  __IOM uint32_t  T1;                           /*!< (@ 0x00000564) End point of 2nd piece wise linear function                */
  __IOM uint32_t  T2;                           /*!< (@ 0x00000568) End point of 3rd piece wise linear function                */
  __IOM uint32_t  T3;                           /*!< (@ 0x0000056C) End point of 4th piece wise linear function                */
  __IOM uint32_t  T4;                           /*!< (@ 0x00000570) End point of 5th piece wise linear function                */
} NRF_TEMP_Type;                                /*!< Size = 1396 (0x574)                                                       */                         /*!< Size = 1396 (0x574)                                                       */
#ifndef NRF_TEMP
#define NRF_TEMP                    ((NRF_TEMP_Type*)          NRF_TEMP_BASE)
#endif
#ifndef NRF_TEMP_BASE
#define NRF_TEMP_BASE               0x4000C000UL
#endif
#endif

#endif