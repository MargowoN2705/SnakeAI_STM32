/**
  ******************************************************************************
  * @file    myai_data_params.h
  * @author  AST Embedded Analytics Research Platform
  * @date    2025-06-14T21:55:41+0200
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#ifndef MYAI_DATA_PARAMS_H
#define MYAI_DATA_PARAMS_H

#include "ai_platform.h"

/*
#define AI_MYAI_DATA_WEIGHTS_PARAMS \
  (AI_HANDLE_PTR(&ai_myai_data_weights_params[1]))
*/

#define AI_MYAI_DATA_CONFIG               (NULL)


#define AI_MYAI_DATA_ACTIVATIONS_SIZES \
  { 1068, }
#define AI_MYAI_DATA_ACTIVATIONS_SIZE     (1068)
#define AI_MYAI_DATA_ACTIVATIONS_COUNT    (1)
#define AI_MYAI_DATA_ACTIVATION_1_SIZE    (1068)



#define AI_MYAI_DATA_WEIGHTS_SIZES \
  { 15372, }
#define AI_MYAI_DATA_WEIGHTS_SIZE         (15372)
#define AI_MYAI_DATA_WEIGHTS_COUNT        (1)
#define AI_MYAI_DATA_WEIGHT_1_SIZE        (15372)



#define AI_MYAI_DATA_ACTIVATIONS_TABLE_GET() \
  (&g_myai_activations_table[1])

extern ai_handle g_myai_activations_table[1 + 2];



#define AI_MYAI_DATA_WEIGHTS_TABLE_GET() \
  (&g_myai_weights_table[1])

extern ai_handle g_myai_weights_table[1 + 2];


#endif    /* MYAI_DATA_PARAMS_H */
