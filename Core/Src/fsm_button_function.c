/*
 * fsm_button_function.c
 *
 *  Created on: Nov 5, 2022
 *      Author: ASUS
 */

#include "fsm_button_function.h"

int counterValue=0;


void changeButtonStatus()
{
	if(isButtonPressed(RESET))
	{
		counterValue=0;
		display7SEG(counterValue);
		buttonStatus=RESET;
	}

	if(isButtonPressed(INC))
	{
		counterValue=(counterValue+1)%10;
		display7SEG(counterValue);
		buttonStatus=INC;
		setTimer1(DO_NOTHING_TIMING);
	}

	if(isButtonPressed(DEC))
	{
		if(counterValue>0)
		{
			counterValue=(counterValue-1)%10;
		}
		else
		{
			counterValue=9;
		}
		display7SEG(counterValue);
		buttonStatus=DEC;
		setTimer1(DO_NOTHING_TIMING);
	}

	if(isTimer1Done())
	{
		if(counterValue>0)
		{
			counterValue=(counterValue-1)%10;
		}
		display7SEG(counterValue);
		buttonStatus=AUTO_DEC;
		setTimer1(1000);
	}
}

void fsm_button_function()
{
	switch(buttonStatus)
	{
	case RESET:
		//TODO
		display7SEG(counterValue);
		changeButtonStatus();
		break;
	case INC:
		//TODO
		changeButtonStatus();
		if(isButtonPressed3s(INC))
		{
			counterValue=(counterValue+1)%10;
			display7SEG(counterValue);
			buttonStatus=INC_1S;
//			setTimer2(1000);
		}
		break;
	case DEC:
		//TODO
		changeButtonStatus();
		if(isButtonPressed3s(DEC))
		{
			if(counterValue>0)
			{
				counterValue=(counterValue-1)%10;
			}
			else
			{
				counterValue=9;
			}
			display7SEG(counterValue);
			buttonStatus=DEC_1S;
//			setTimer2(1000);
		}
		break;
	case AUTO_DEC:
		//TODO
		changeButtonStatus();
		break;
	case INC_1S:
		if(isButtonPressed3s(INC)==1)
		{
			counterValue=(counterValue+1)%10;
			display7SEG(counterValue);
//			setTimer2(1000);
		}
		else
		{
			buttonStatus=INC;
			setTimer1(DO_NOTHING_TIMING);
		}
		break;
	case DEC_1S:
		if(isButtonPressed3s(DEC)==1)
		{
				if(counterValue>0)
				{
					counterValue=(counterValue-1)%10;
				}
				else
				{
					counterValue=9;
				}
				display7SEG(counterValue);
				buttonStatus=DEC_1S;
//				setTimer2(1000);
		}
		else
		{
			buttonStatus=DEC;
			setTimer1(DO_NOTHING_TIMING);
		}
		break;

	default:
		break;
	}
}



