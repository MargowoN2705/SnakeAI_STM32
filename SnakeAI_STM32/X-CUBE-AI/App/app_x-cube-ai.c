
/**
  ******************************************************************************
  * @file    app_x-cube-ai.c
  * @author  X-CUBE-AI C code generator
  * @brief   AI program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

 /*
  * Description
  *   v1.0 - Minimum template to show how to use the Embedded Client API
  *          model. Only one input and one output is supported. All
  *          memory resources are allocated statically (AI_NETWORK_XX, defines
  *          are used).
  *          Re-target of the printf function is out-of-scope.
  *   v2.0 - add multiple IO and/or multiple heap support
  *
  *   For more information, see the embeded documentation:
  *
  *       [1] %X_CUBE_AI_DIR%/Documentation/index.html
  *
  *   X_CUBE_AI_DIR indicates the location where the X-CUBE-AI pack is installed
  *   typical : C:\Users\[user_name]\STM32Cube\Repository\STMicroelectronics\X-CUBE-AI\7.1.0
  */

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#if defined ( __ICCARM__ )
#elif defined ( __CC_ARM ) || ( __GNUC__ )
#endif

/* System headers */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "app_x-cube-ai.h"
#include "main.h"
#include "ai_datatypes_defines.h"
#include "myai.h"
#include "myai_data.h"

/* USER CODE BEGIN includes */
#include "../Core/Src/Snake_Game.h"
#define STATE_SIZE 11
#define OUTPUT_SIZE 3

/* USER CODE END includes */

/* IO buffers ----------------------------------------------------------------*/

#if !defined(AI_MYAI_INPUTS_IN_ACTIVATIONS)
AI_ALIGNED(4) ai_i8 data_in_1[AI_MYAI_IN_1_SIZE_BYTES];
ai_i8* data_ins[AI_MYAI_IN_NUM] = {
data_in_1
};
#else
ai_i8* data_ins[AI_MYAI_IN_NUM] = {
NULL
};
#endif

#if !defined(AI_MYAI_OUTPUTS_IN_ACTIVATIONS)
AI_ALIGNED(4) ai_i8 data_out_1[AI_MYAI_OUT_1_SIZE_BYTES];
ai_i8* data_outs[AI_MYAI_OUT_NUM] = {
data_out_1
};
#else
ai_i8* data_outs[AI_MYAI_OUT_NUM] = {
NULL
};
#endif

/* Activations buffers -------------------------------------------------------*/

AI_ALIGNED(32)
static uint8_t pool0[AI_MYAI_DATA_ACTIVATION_1_SIZE];

ai_handle data_activations0[] = {pool0};

/* AI objects ----------------------------------------------------------------*/

static ai_handle myai = AI_HANDLE_NULL;

static ai_buffer* ai_input;
static ai_buffer* ai_output;

static void ai_log_err(const ai_error err, const char *fct)
{
  /* USER CODE BEGIN log */
  if (fct)
    printf("TEMPLATE - Error (%s) - type=0x%02x code=0x%02x\r\n", fct,
        err.type, err.code);
  else
    printf("TEMPLATE - Error - type=0x%02x code=0x%02x\r\n", err.type, err.code);

  do {} while (1);
  /* USER CODE END log */
}

static int ai_boostrap(ai_handle *act_addr)
{
  ai_error err;

  /* Create and initialize an instance of the model */
  err = ai_myai_create_and_init(&myai, act_addr, NULL);
  if (err.type != AI_ERROR_NONE) {
    ai_log_err(err, "ai_myai_create_and_init");
    return -1;
  }

  ai_input = ai_myai_inputs_get(myai, NULL);
  ai_output = ai_myai_outputs_get(myai, NULL);

#if defined(AI_MYAI_INPUTS_IN_ACTIVATIONS)
  /*  In the case where "--allocate-inputs" option is used, memory buffer can be
   *  used from the activations buffer. This is not mandatory.
   */
  for (int idx=0; idx < AI_MYAI_IN_NUM; idx++) {
	data_ins[idx] = ai_input[idx].data;
  }
#else
  for (int idx=0; idx < AI_MYAI_IN_NUM; idx++) {
	  ai_input[idx].data = data_ins[idx];
  }
#endif

#if defined(AI_MYAI_OUTPUTS_IN_ACTIVATIONS)
  /*  In the case where "--allocate-outputs" option is used, memory buffer can be
   *  used from the activations buffer. This is no mandatory.
   */
  for (int idx=0; idx < AI_MYAI_OUT_NUM; idx++) {
	data_outs[idx] = ai_output[idx].data;
  }
#else
  for (int idx=0; idx < AI_MYAI_OUT_NUM; idx++) {
	ai_output[idx].data = data_outs[idx];
  }
#endif

  return 0;
}

static int ai_run(void)
{
  ai_i32 batch;

  batch = ai_myai_run(myai, ai_input, ai_output);
  if (batch != 1) {
    ai_log_err(ai_myai_get_error(myai),
        "ai_myai_run");
    return -1;
  }

  return 0;
}

/* USER CODE BEGIN 2 */
int acquire_and_process_data(ai_i8* data[])
{
  /* fill the inputs of the c-model
  for (int idx=0; idx < AI_NETWORK_1_IN_NUM; idx++ )
  {
      data[idx] = ....
  }

  */
  return 0;
}

int post_process(ai_i8* data[])
{
  /* process the predictions
  for (int idx=0; idx < AI_NETWORK_1_OUT_NUM; idx++ )
  {
      data[idx] = ....
  }

  */
  return 0;
}

void runAI(int state[STATE_SIZE], float output[OUTPUT_SIZE]) {
    // 1. Wskazanie na dane wejściowe modelu
    float* input_data = (float*)ai_input->data;

    // 2. Skopiuj dane z int[] do float[]
    for (int i = 0; i < STATE_SIZE; i++) {
        input_data[i] = (float)state[i];
    }

    // 3. Uruchom sieć neuronową
    if (ai_run() != 0) {
        // Błąd działania sieci – możesz dodać np. miganie LED
        return;
    }

    // 4. Pobierz dane wyjściowe
    float* result = (float*)ai_output->data;
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        output[i] = result[i];
    }
}
/* USER CODE END 2 */

/* Entry points --------------------------------------------------------------*/

void MX_X_CUBE_AI_Init(void)
{
    /* USER CODE BEGIN 5 */
  printf("\r\nTEMPLATE - initialization\r\n");

  ai_boostrap(data_activations0);
    /* USER CODE END 5 */
}

void MX_X_CUBE_AI_Process(void)
{
    /* USER CODE BEGIN 6 */

    /* USER CODE END 6 */
}

#ifdef __cplusplus
}
#endif
