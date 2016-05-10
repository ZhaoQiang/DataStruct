/******************************************************************************
 * File         : branchPrediction.h
 * Date Created : 26/2/2008
 * Contents     : use gcc __builtin_expect to steer gcc in the right direction.
 ******************************************************************************
 * (C) COPYRIGHT AGILENT TECHNOLOGIES UK LTD 2008. ALL RIGHTS RESERVED.
 * NO PART OF THIS PROGRAM MAY BE PHOTOCOPIED REPRODUCED OR TRANSLATED
 * TO ANOTHER PROGRAM LANGUAGE WITHOUT THE PRIOR WRITTEN CONSENT OF
 * AGILENT TECHNOLOGIES UK LTD.
 *****************************************************************************/


#ifndef __ASD_BRANCH_PREDICTION_H__
#define __ASD_BRANCH_PREDICTION_H__

/* Branch prediction macros */
#define predict_true( x ) __builtin_expect( !!( x ), 1 ) 
#define predict_false( x ) __builtin_expect( !!( x ), 0 ) 

#endif

