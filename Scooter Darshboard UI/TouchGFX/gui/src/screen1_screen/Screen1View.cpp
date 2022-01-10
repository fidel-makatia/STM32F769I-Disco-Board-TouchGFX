#include <gui/screen1_screen/Screen1View.hpp>
#include <BitmapDatabase.hpp>
#include "stm32f7xx_hal.h"


int check=0;
int count=0;

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::updateIconAndText()
{
	 if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)==GPIO_PIN_SET)
	   {
		   HAL_Delay(50);
		   if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)==GPIO_PIN_SET)
		   {
			   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
			   imagecar.setBitmap(Bitmap(BITMAP_CAR03_ID));
			   lefticon.setBitmap(Bitmap(BITMAP_LEFT03_ID));

			   count++;
		   }
		   else
		   {
			   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
			   imagecar.setBitmap(Bitmap(BITMAP_CAR02_ID));
			   lefticon.setBitmap(Bitmap(BITMAP_LEFT02_ID));

		   }

//		   if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)==GPIO_PIN_SET && count==2)
//		   {
//			   righticon.setBitmap(Bitmap(BITMAP_RIGHT03_ID));
//			   count=0;
//
//		   }
//		   else
//		   {
//			   righticon.setBitmap(Bitmap(BITMAP_RIGHT02_ID));
//
//		   }

	   }
}

void Screen1View::updateGuage(uint16_t value)
{
    gauge1.updateValue(value, 0);
    gauge2.updateValue(value, 0);

    Unicode::snprintf(speedtxtBuffer, SPEEDTXT_SIZE, "%d", value);
    // Invalidate text area, which will result in it being redrawn in next tick.
    speedtxt.invalidate();
    Unicode::snprintf(rpmtxtBuffer, RPMTXT_SIZE, "%d", (value/10));
    // Invalidate text area, which will result in it being redrawn in next tick.
    rpmtxt.invalidate();

    if (value>=90)
    {


    	if(check==0 || check==3000)
    		modalWindow1.show();
    	check++;
    	//HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_3, GPIO_PIN_SET);


    }
    else
    {
    	modalWindow1.hide();
    	check=0;
    	//HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_3, GPIO_PIN_RESET);
    }
    if (value>=70)
    {



    	HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_3, GPIO_PIN_SET);
    	alarm.setBitmap(Bitmap(BITMAP_ALARM01_ID));


    }
    else
    {

    	HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_3, GPIO_PIN_RESET);
    	alarm.setBitmap(Bitmap(BITMAP_ALARM00_ID));
    }

    updateIconAndText();
}
