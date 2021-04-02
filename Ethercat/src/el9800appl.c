/**
\addtogroup EL9800Appl EL9800 application
@{
*/

/**
\file el9800appl.c
\author EthercatSSC@beckhoff.com
\brief Implementation

\version 5.11

<br>Changes to version V5.10:<br>
V5.11 ECAT11: create application interface function pointer, add eeprom emulation interface functions<br>
V5.11 EL9800 1: reset outputs on fallback from OP state<br>
<br>Changes to version V5.01:<br>
V5.10 ECAT6: Add "USE_DEFAULT_MAIN" to enable or disable the main function<br>
<br>Changes to version V5.0:<br>
V5.01 EL9800 2: Add TxPdo Parameter object 0x1802<br>
<br>Changes to version V4.30:<br>
V4.50 ECAT2: Create generic application interface functions. Documentation in Application Note ET9300.<br>
V4.50 COE2: Handle invalid PDO assign values.<br>
V4.30 : create file
*/


/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include "ecat_def.h"
#include "includes.h"
#if EL9800_APPLICATION

/* ECATCHANGE_START(V5.11) ECAT11*/
#include "applInterface.h"
/* ECATCHANGE_END(V5.11) ECAT11*/

//#include "el9800hw.h"

#define _EVALBOARD_
#include "el9800appl.h"
#undef _EVALBOARD_

#if MCI_HW
#include "mcihw.h"
#endif
#if EL9800_HW
#include "el9800hw.h"
#endif



/*--------------------------------------------------------------------------------------
------
------    local types and defines
------
--------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    local variables and constants
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    application specific functions
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    generic functions
------
-----------------------------------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    The function is called when an error state was acknowledged by the master

*////////////////////////////////////////////////////////////////////////////////////////

void    APPL_AckErrorInd(UINT16 stateTrans)
{ 
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from INIT to PREOP when
           all general settings were checked to start the mailbox handler. This function
           informs the application about the state transition, the application can refuse
           the state transition when returning an AL Status error code.
           The return code NOERROR_INWORK can be used, if the application cannot confirm
           the state transition immediately, in that case the application need to be complete 
           the transition by calling ECAT_StateChange.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartMailboxHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from PREEOP to INIT
             to stop the mailbox handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopMailboxHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param    pIntMask    pointer to the AL Event Mask which will be written to the AL event Mask
                        register (0x204) when this function is succeeded. The event mask can be adapted
                        in this function
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from PREOP to SAFEOP when
             all general settings were checked to start the input handler. This function
             informs the application about the state transition, the application can refuse
             the state transition when returning an AL Status error code.
            The return code NOERROR_INWORK can be used, if the application cannot confirm
            the state transition immediately, in that case the application need to be complete 
            the transition by calling ECAT_StateChange.
*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartInputHandler(UINT16 *pIntMask)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from SAFEOP to PREEOP
             to stop the input handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopInputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from SAFEOP to OP when
             all general settings were checked to start the output handler. This function
             informs the application about the state transition, the application can refuse
             the state transition when returning an AL Status error code.
           The return code NOERROR_INWORK can be used, if the application cannot confirm
           the state transition immediately, in that case the application need to be complete 
           the transition by calling ECAT_StateChange.
*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartOutputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from OP to SAFEOP
             to stop the output handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopOutputHandler(void)
{
/*ECATCHANGE_START(V5.11) EL9800 1*/
//    sDOOutputs.bLED1 = 0;
//    sDOOutputs.bLED2 = 0;
//    sDOOutputs.bLED3 = 0;
//    sDOOutputs.bLED4 = 0;
//#if _STM32_IO8
//    sDOOutputs.bLED5 = 0;
//    sDOOutputs.bLED7 = 0;
//    sDOOutputs.bLED6 = 0;
//    sDOOutputs.bLED8 = 0;
//#endif
//    
//    LED_1                        = sDOOutputs.bLED1;
//    LED_2                        = sDOOutputs.bLED2;
//    LED_3                        = sDOOutputs.bLED3;
//    LED_4                        = sDOOutputs.bLED4;
//#if _STM32_IO8
//    LED_5                        = sDOOutputs.bLED5;
//    LED_7                        = sDOOutputs.bLED7;
//    LED_6                        = sDOOutputs.bLED6;
//    LED_8                        = sDOOutputs.bLED8;
//#endif
/*ECATCHANGE_END(V5.11) EL9800 1*/
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\return     0(ALSTATUSCODE_NOERROR), NOERROR_INWORK
\param      pInputSize  pointer to save the input process data length
\param      pOutputSize  pointer to save the output process data length

\brief    This function calculates the process data sizes from the actual SM-PDO-Assign
            and PDO mapping
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 APPL_GenerateMapping(UINT16* pInputSize,UINT16* pOutputSize)
{
#if COE_SUPPORTED
    UINT16 result = ALSTATUSCODE_NOERROR;
    UINT16 PDOAssignEntryCnt = 0;
    OBJCONST TOBJECT OBJMEM * pPDO = NULL;
    UINT16 PDOSubindex0 = 0;
    UINT32 *pPDOEntry = NULL;
    UINT16 PDOEntryCnt = 0;
    UINT16 InputSize = 0;
    UINT16 OutputSize = 0;

    /*Scan object 0x1C12 RXPDO assign*/
    for(PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sRxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
    {
        pPDO = OBJ_GetObjectHandle(sRxPDOassign.aEntries[PDOAssignEntryCnt]);
        if(pPDO != NULL)
        {
            PDOSubindex0 = *((UINT16 *)pPDO->pVarPtr);
            for(PDOEntryCnt = 0; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++)
            {
			//				result = *(UINT8 *)pPDO->pVarPtr;
			//				result=(OBJ_GetEntryOffset((PDOEntryCnt+1),pPDO)>>3);
                pPDOEntry = (UINT32 *)((UINT8 *)pPDO->pVarPtr + (OBJ_GetEntryOffset((PDOEntryCnt+1),pPDO)>>3));    //goto PDO entry
                // we increment the expected output size depending on the mapped Entry
                OutputSize += (UINT16) ((*pPDOEntry) & 0xFF);
            }
        }
        else
        {
            /*assigned PDO was not found in object dictionary. return invalid mapping*/
            OutputSize = 0;
            result = ALSTATUSCODE_INVALIDOUTPUTMAPPING;
            break;
        }
    }

    OutputSize = (OutputSize + 7) >> 3;

    if(result == 0)
    {
        /*Scan Object 0x1C13 TXPDO assign*/
        for(PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sTxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
        {
            pPDO = OBJ_GetObjectHandle(sTxPDOassign.aEntries[PDOAssignEntryCnt]);
            if(pPDO != NULL)
            {
                PDOSubindex0 = *((UINT16 *)pPDO->pVarPtr);
                for(PDOEntryCnt = 0; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++)
                {
                    pPDOEntry = (UINT32 *)((UINT8 *)pPDO->pVarPtr + (OBJ_GetEntryOffset((PDOEntryCnt+1),pPDO)>>3));    //goto PDO entry
                    // we increment the expected output size depending on the mapped Entry
                    InputSize += (UINT16) ((*pPDOEntry) & 0xFF);
                }
            }
            else
            {
                /*assigned PDO was not found in object dictionary. return invalid mapping*/
                InputSize = 0;
                result = ALSTATUSCODE_INVALIDINPUTMAPPING;
                break;
            }
        }
    }
    InputSize = (InputSize + 7) >> 3;

    *pInputSize = InputSize;
    *pOutputSize = OutputSize;
    return result;
#else
    *pInputSize = 6;
    *pOutputSize = 2;
    return ALSTATUSCODE_NOERROR;
#endif

}


/////////////////////////////////////////////////////////////////////////////////////////
/**
\param      pData  pointer to input process data
\brief      This function will copies the inputs from the local memory to the ESC memory
            to the hardware
*////////////////////////////////////////////////////////////////////////////////////////
#if _STM32_IO4 && AL_EVENT_ENABLED
/* the pragma interrupt_level is used to tell the compiler that these functions will not
   be called at the same time from the main function and the interrupt routine */
#pragma interrupt_level 1
#endif
void APPL_InputMapping(UINT16* pData)
{
    UINT16 j = 0;
    UINT16 *pTmpData = (UINT16 *)pData;
    /* we go through all entries of the TxPDO Assign object to get the assigned TxPDOs */
   for (j = 0; j < sTxPDOassign.u16SubIndex0; j++)
   {
      switch (sTxPDOassign.aEntries[j])
      {
      /* TxPDO 1 */
      case 0x1A00:
         *pTmpData++ = SWAPWORD(((UINT16 *) &AD_Inputs)[1]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &AD_Inputs)[2]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &AD_Inputs)[3]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &AD_Inputs)[4]);
         break;
			/* TxPDO 2 */
      case 0x1A01:
         *pTmpData++ = SWAPWORD(((UINT16 *) &AD_Switch_Status_OUT)[1]);
				 *pTmpData++ = SWAPWORD(((UINT16 *) &AD_Switch_Status_OUT)[2]);
				 *pTmpData++ = SWAPWORD(((UINT16 *) &AD_Switch_Status_OUT)[3]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &AD_Switch_Status_OUT)[4]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &AD_Switch_Status_OUT)[5]);
         break;
      /* TxPDO 3 */
      case 0x1A02:
			   *pTmpData++ = SWAPWORD(((UINT16 *) &Current_Inputs)[2]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &Current_Inputs)[3]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &Current_Inputs)[4]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &Current_Inputs)[5]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &Current_Inputs)[6]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &Current_Inputs)[7]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &Current_Inputs)[8]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &Current_Inputs)[9]);
         break;
			case 0x1A03:
			   *pTmpData++ = SWAPWORD(((UINT16 *) &Diancifa_STATUS_6030)[1]);
				 *pTmpData++ = SWAPWORD(((UINT16 *) &Diancifa_STATUS_6030)[2]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &Diancifa_STATUS_6030)[3]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &Diancifa_STATUS_6030)[4]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &Diancifa_STATUS_6030)[5]);
         break;
			case 0x1A04:
			   *pTmpData++ = SWAPWORD(((UINT16 *) &Selfcheck_STATUS_6040)[1]);
         break;
			case 0x1A05:
			   *pTmpData++ = SWAPWORD(((UINT16 *) &ECMK_INFO_6050)[1]);
				 *pTmpData++ = SWAPWORD(((UINT16 *) &ECMK_INFO_6050)[2]);
				 *pTmpData++ = SWAPWORD(((UINT16 *) &ECMK_INFO_6050)[3]);
				 *pTmpData++ = SWAPWORD(((UINT16 *) &ECMK_INFO_6050)[4]);
				 *pTmpData++ = SWAPWORD(((UINT16 *) &ECMK_INFO_6050)[5]);
				 *pTmpData++ = SWAPWORD(((UINT16 *) &ECMK_INFO_6050)[6]);
				 *pTmpData++ = SWAPWORD(((UINT16 *) &ECMK_INFO_6050)[7]);
				 *pTmpData++ = SWAPWORD(((UINT16 *) &ECMK_INFO_6050)[8]);
			
				 //*pTmpData++ = SWAPWORD(((UINT16 *) &ECMK_INFO_6050)[9]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &ECMK_INFO_6050)[10]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &ECMK_INFO_6050)[11]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &ECMK_INFO_6050)[12]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &ECMK_INFO_6050)[13]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &ECMK_INFO_6050)[14]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &ECMK_INFO_6050)[15]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &ECMK_INFO_6050)[16]);
			   *pTmpData++ = SWAPWORD(((UINT16 *) &ECMK_INFO_6050)[17]);
         break;
      }
   }
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\param      pData  pointer to output process data

\brief    This function will copies the outputs from the ESC memory to the local memory
            to the hardware
*////////////////////////////////////////////////////////////////////////////////////////
#if _STM32_IO4  && AL_EVENT_ENABLED
/* the pragma interrupt_level is used to tell the compiler that these functions will not
   be called at the same time from the main function and the interrupt routine */
#pragma interrupt_level 1
#endif
void APPL_OutputMapping(UINT16* pData)
{
    UINT16 j = 0;
    UINT16 *pTmpData = (UINT16 *)pData;

    /* we go through all entries of the RxPDO Assign object to get the assigned RxPDOs */
    for (j = 0; j < sRxPDOassign.u16SubIndex0; j++)
    {
        switch (sRxPDOassign.aEntries[j])
        {
        /* RxPDO 2 */
        case 0x1601:
            ((UINT16 *) &AD_Switch_Cmd)[1] = SWAPWORD(*pTmpData++);
						((UINT16 *) &AD_Switch_Cmd)[2] = SWAPWORD(*pTmpData++);
						((UINT16 *) &AD_Switch_Cmd)[3] = SWAPWORD(*pTmpData++);
						((UINT16 *) &AD_Switch_Cmd)[4] = SWAPWORD(*pTmpData++);
						((UINT16 *) &AD_Switch_Cmd)[5] = SWAPWORD(*pTmpData++);
            break;
				case 0x1602:
            ((UINT16 *) &Diancifa_cmd)[1] = SWAPWORD(*pTmpData++);
						((UINT16 *) &Diancifa_cmd)[2] = SWAPWORD(*pTmpData++);
						((UINT16 *) &Diancifa_cmd)[3] = SWAPWORD(*pTmpData++);
						((UINT16 *) &Diancifa_cmd)[4] = SWAPWORD(*pTmpData++);
						((UINT16 *) &Diancifa_cmd)[5] = SWAPWORD(*pTmpData++);
            break;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\brief    This function will called from the synchronisation ISR 
            or from the mainloop if no synchronisation is supported
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_Application(void)
{
	//	*pRet=ad;
#if _STM32_IO4
    UINT16 analogValue;
#endif
	//同步ad的值
	//AD_Inputs.CH1=CH1_AD_Inputs;
	//AD_Inputs.CH2=CH2_AD_Inputs;
	//AD_Inputs.CH3=CH3_AD_Inputs;
	//AD_Inputs.CH4=CH4_AD_Inputs;
  //同步电流的值
	Current_Inputs.CH_CURRENT[0]=CH1_current;
	Current_Inputs.CH_CURRENT[1]=CH2_current;
	Current_Inputs.CH_CURRENT[2]=CH3_current;
	Current_Inputs.CH_CURRENT[3]=CH4_current;
	//同步参数能否更改的值
	AD_Switch_Status_OUT.CH1_ENABLE=AD_Switch_Cmd.CH1_ENABLE;
	AD_Switch_Status_OUT.CH2_ENABLE=AD_Switch_Cmd.CH2_ENABLE;
	AD_Switch_Status_OUT.CH3_ENABLE=AD_Switch_Cmd.CH3_ENABLE;
	AD_Switch_Status_OUT.CH4_ENABLE=AD_Switch_Cmd.CH4_ENABLE;
	//同步频率的值
	if (AD_Switch_Status_OUT.CH1_ENABLE)
		AD_Switch_Status_OUT.CH1_Frequency=AD_Switch_Cmd.CH1_Frequency;
	if (AD_Switch_Status_OUT.CH2_ENABLE)
		AD_Switch_Status_OUT.CH2_Frequency=AD_Switch_Cmd.CH2_Frequency;
	if (AD_Switch_Status_OUT.CH3_ENABLE)
		AD_Switch_Status_OUT.CH3_Frequency=AD_Switch_Cmd.CH3_Frequency;
	if (AD_Switch_Status_OUT.CH4_ENABLE)
		AD_Switch_Status_OUT.CH4_Frequency=AD_Switch_Cmd.CH4_Frequency;
	
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param     index               index of the requested object.
 \param     subindex            subindex of the requested object.
 \param     objSize             size of the requested object data, calculated with OBJ_GetObjectLength
 \param     pData               Pointer to the buffer where the data can be copied to
 \param     bCompleteAccess     Indicates if a complete read of all subindices of the
                                object shall be done or not

 \return    ABORTIDX_XXX

 \brief     Handles SDO read requests to TxPDO Parameter
*////////////////////////////////////////////////////////////////////////////////////////
UINT8 ReadObject0x1802( UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess )
{

    if(bCompleteAccess)
        return ABORTIDX_UNSUPPORTED_ACCESS;

    if(subindex == 0)
    {
        *pData = TxPDO1802Subindex0;
    }
    else if(subindex == 6)
    {
        /*clear destination buffer (no excluded TxPDO set)*/
        if(dataSize > 0)
            MBXMEMSET(pData,0x00,dataSize);
    }
    else if(subindex == 7)
    {
//        /*min size is one Byte*/
//        UINT8 *pu8Data = (UINT8*)pData;
//        
//        //Reset Buffer
//        *pu8Data = 0; 

//        *pu8Data = sAIInputs.bTxPDOState;
    }
    else if(subindex == 9)
    {
//        /*min size is one Byte*/
//        UINT8 *pu8Data = (UINT8*)pData;
//        
//        //Reset Buffer
//        *pu8Data = 0; 

//        *pu8Data = sAIInputs.bTxPDOToggle;
    }
    else
        return ABORTIDX_SUBINDEX_NOT_EXISTING;

    return 0;
}

#if EXPLICIT_DEVICE_ID
/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    The Explicit Device ID of the EtherCAT slave

 \brief     Calculate the Explicit Device ID
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 APPL_GetDeviceID()
{
    UINT16 Value = (UINT16)(SWITCH_8<<7)|(SWITCH_7<<6)|(SWITCH_6<<5)|(SWITCH_5<<4)|(SWITCH_4<<3)|(SWITCH_3<<2)|(SWITCH_2<<1)|(SWITCH_1);
    return Value;
}
#endif

#if USE_DEFAULT_MAIN
/////////////////////////////////////////////////////////////////////////////////////////
/**

 \brief    This is the main function

*////////////////////////////////////////////////////////////////////////////////////////

 
#if _STM32_IO8
int main(void)
#else
void main(void)
#endif
{
    /* initialize the Hardware and the EtherCAT Slave Controller */
    HW_Init();

    MainInit();

    bRunApplication = TRUE;
    do
    {
        MainLoop();						
    } while (bRunApplication == TRUE);

    HW_Release();
#if _STM32_IO8
    return 0;
#endif
}
#endif //#if USE_DEFAULT_MAIN
#endif //#if EL9800_APPLICATION

/** @} */
