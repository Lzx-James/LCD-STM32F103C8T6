/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd_spi_096.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void 	LCD_Test_Clear(void);			// ????????
void 	LCD_Test_Text(void);			   // ???????
void 	LCD_Test_Variable (void);	   // ???????????????????С??
void 	LCD_Test_Color(void);			// ??????????
void 	LCD_Test_Grahic(void);		   // 2D??λ???
void 	LCD_Test_Image(void);			// ?????
void  LCD_Test_Direction(void);	   // ???????????
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

// 为了传输效率，本例程的SPI通信采用寄存器操作，不用HAL库自带的收发函数，所以需要单独配置下面2个
    __HAL_SPI_ENABLE(&LCD_SPI);   // 使能SPI
    SPI_1LINE_TX(&LCD_SPI);       // 单线发送模式

    SPI_LCD_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      LCD_Test_Clear(); 		// ????????
//      LCD_Test_Text();			// ???????
//      LCD_Test_Variable();		// ???????????????????С??
//      LCD_Test_Color();			// ???????
      LCD_Test_Grahic();		// 2D??λ???
      LCD_Test_Image();			// ?????
      LCD_Test_Direction();	// ???????????
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/*************************************************************************************************
*	?? ?? ??:	LCD_Test_Clear
*https://shop252966792.taobao.com
*	????????:	????????
*************************************************************************************************/
void LCD_Test_Clear(void)
{
    uint8_t	i = 0;			// ????????

    LCD_SetDirection(Direction_H_Flip);
    LCD_SetTextFont(&CH_Font16);			// ????2424????????,ASCII???????2412
    LCD_SetColor(LCD_BLACK);				// ??????????

    for(i=0;i<8;i++)
    {
        switch (i)		// ?л??????
        {
            case 0: LCD_SetBackColor(LIGHT_RED); 		break;
            case 1: LCD_SetBackColor(LIGHT_GREEN); 	break;
            case 2: LCD_SetBackColor(LIGHT_BLUE); 		break;
            case 3: LCD_SetBackColor(LIGHT_YELLOW); 	break;
            case 4: LCD_SetBackColor(LIGHT_CYAN);		break;
            case 5: LCD_SetBackColor(LIGHT_GREY); 		break;
            case 6: LCD_SetBackColor(LIGHT_MAGENTA); 	break;
            case 7: LCD_SetBackColor(LCD_WHITE); 		break;
            default:	break;
        }
        LCD_Clear();		// ????
        LCD_DisplayText(13, 5,"STM32 ???????");
        LCD_DisplayText(13,30,"????????:160*80");
        LCD_DisplayText(13,55,"??????:ST7735");
        HAL_Delay(1000);	// ???
    }
}

/*************************************************************************************************
*	?? ?? ??:	LCD_Test_Text
*
*	????????:	??????????
*https://shop252966792.taobao.com
*	?    ??:	?????????????????????С???????ASCII???
*************************************************************************************************/
void LCD_Test_Text(void)
{
    LCD_SetBackColor(LCD_BLACK); 			//	????????
    LCD_Clear(); 								// ????

    LCD_SetColor(LCD_CYAN);
//    LCD_SetAsciiFont(&ASCII_Font12); LCD_DisplayString(0,  0,"ASCII:12*12");
//    LCD_SetAsciiFont(&ASCII_Font16); LCD_DisplayString(0, 12,"ASCII:16*16");
//    LCD_SetAsciiFont(&ASCII_Font20); LCD_DisplayString(0, 28,"ASCII:20*20");
//    LCD_SetColor(LCD_WHITE);
//    LCD_SetAsciiFont(&ASCII_Font24); LCD_DisplayString(0, 48,"ASCII:2424");
//    LCD_SetColor(LCD_YELLOW);
//    LCD_SetAsciiFont(&ASCII_Font32); LCD_DisplayString(135, 25,"*");
//    LCD_SetAsciiFont(&ASCII_Font32); LCD_DisplayString(128,  0,"32"); LCD_DisplayString(128,  48,"32");

    HAL_Delay(2000);	// ??????
    LCD_Clear(); 								// ????

    LCD_SetTextFont(&CH_Font12);			// ????1212????????,ASCII???????1206
    LCD_SetColor(0X8AC6D1);					// ???????
    LCD_DisplayText(0, 0,"1212:??????");

    LCD_SetTextFont(&CH_Font16);			// ????1616????????,ASCII???????1608
    LCD_SetColor(0XC5E1A5);					// ???????
    LCD_DisplayText(0, 12,"1616:??????");

    LCD_SetTextFont(&CH_Font20);			// ????2020????????,ASCII???????2010
    LCD_SetColor(0XFFB549);					// ???????
    LCD_DisplayText(0, 28,"2020:??????");

    LCD_SetTextFont(&CH_Font24);			// ????2424????????,ASCII???????2412
    LCD_SetColor(0XFF585D);					// ???????
    LCD_DisplayText(0, 48,"2424:??????");


    HAL_Delay(2000);	// ??????
}
/************************************************************************************************
*	?? ?? ??:	LCD_Test_Variable
*https://shop252966792.taobao.com
*	????????:	???????????????????С??
*************************************************************************************************/
void LCD_Test_Variable (void)
{
    uint16_t i;					// ????????
    int32_t	a = 0;			// ?????????????????????
    int32_t	b = 0;			// ?????????????????????
    int32_t	c = 0;			// ?????????????????????

    double f = -1234.1234;	// ???帡?????????????????

    LCD_SetBackColor(LCD_BLACK); 			//	????????
    LCD_Clear(); 								// ????

    LCD_SetTextFont(&CH_Font16);
    LCD_SetColor(LIGHT_CYAN);					// ?????????????
    LCD_DisplayText(0, 0,"????:");

    LCD_SetColor(LIGHT_YELLOW);				// ?????????????
    LCD_DisplayText(0,20,"?????:");
    LCD_DisplayText(0,40,"???0:");

    LCD_SetColor(LIGHT_RED);					// ???????	???????
    LCD_DisplayText(0,60,"С??:");


    for(i=0;i<100;i++)
    {
        LCD_SetColor(LIGHT_CYAN);								// ???????	???????
        LCD_ShowNumMode(Fill_Space);							// ????λ?????
        LCD_DisplayNumber( 50,0, b+i*10, 4) ;				// ???????
        LCD_DisplayNumber( 100,0, c-i*10, 4) ;				// ???????

        LCD_SetColor(LIGHT_YELLOW);								// ?????????????

        LCD_ShowNumMode(Fill_Space);								// ????λ??? ???
        LCD_DisplayNumber( 80,20, a+i*150, 8) ;				// ???????

        LCD_ShowNumMode(Fill_Zero);								// ????λ???0
        LCD_DisplayNumber( 80,40, b+i*150, 8) ;				// ???????

        LCD_SetColor(LIGHT_RED);									// ?????????????
        LCD_ShowNumMode(Fill_Space);								// ????λ?????
        LCD_DisplayDecimals( 50,60, f+i*0.01, 11,4);		// ???С??

        HAL_Delay(15);
    }
    HAL_Delay(2500);
}
/*************************************************************************************************
*	?? ?? ??:	LCD_Test_Color
*https://shop252966792.taobao.com
*	????????:	?????
*************************************************************************************************/
void LCD_Test_Color(void)
{
    uint16_t i;					// ????????
    uint16_t y;
// ???????>>>>>
    LCD_SetBackColor(LCD_BLACK); //????????
    LCD_Clear(); //????????????

    LCD_SetTextFont(&CH_Font16);			// ????????
    LCD_SetColor(LCD_WHITE);				// ??????????
    LCD_DisplayText(0,0,"RGB?????:");

    //?????????????????????
    for(i=0;i<160;i++)
    {
        LCD_SetColor( LCD_RED-(i<<16) );
        LCD_DrawLine_V(0+i,  20,10);
    }
    for(i=0;i<240;i++)
    {
        LCD_SetColor( LCD_GREEN-(i<<8) );
        LCD_DrawLine_V(0+i,  30,10);
    }
    for(i=0;i<240;i++)
    {
        LCD_SetColor( LCD_BLUE-i );
        LCD_DrawLine_V(0+i,  40,10);
    }

    y = 50;
    LCD_SetColor(LIGHT_CYAN);    LCD_FillRect(85,y+5     ,75,10);  LCD_DisplayString(0,y     ,"LIGHT_CYAN");
    LCD_SetColor(LIGHT_MAGENTA); LCD_FillRect(105,y+16*1+5,55,10);  LCD_DisplayString(0,y+16*1,"LIGHT_MAGENTA");

    HAL_Delay(2000);
}

/*************************************************************************************************
*	?? ?? ??:	LCD_Test_Grahic
*
*	????????:	2D??λ???
*************************************************************************************************/
void LCD_Test_Grahic(void)
{
    LCD_SetBackColor(LCD_BLACK); //????????
    LCD_Clear(); //????????????

    LCD_SetColor(LCD_WHITE);
    LCD_DrawRect(0,0,160,80); 			//???????

    LCD_SetColor(LCD_RED);    LCD_FillCircle(50,40,30);		//??????
    LCD_SetColor(LCD_GREEN);  LCD_FillCircle(80,40,30);
    LCD_SetColor(LCD_BLUE);   LCD_FillCircle(110,40,30);

    HAL_Delay(1000);
    LCD_Clear(); //????????????

    LCD_SetColor(LIGHT_CYAN);
    LCD_DrawCircle(80,40,30);			//???????
    LCD_DrawCircle(80,40,20);

    LCD_SetColor(LIGHT_RED);
    LCD_DrawEllipse(80,40,70,28); 	//???????
    LCD_DrawEllipse(80,40,60,35); 	//???????

    HAL_Delay(1000);
}
/*************************************************************************************************
*	?? ?? ??:	LCD_Test_Image
*
*	????????:	?????????
*************************************************************************************************/
void LCD_Test_Image(void)
{
    LCD_SetBackColor(LCD_BLACK); 			//	????????
    LCD_Clear(); 								// ????

    LCD_SetColor( 0xffF6E58D);
    LCD_DrawImage( 10, 10, 60, 60, Image_Android_60x60) ;	   // ?????

    LCD_SetColor( 0xff9DD3A8);
    LCD_DrawImage( 90, 10, 60, 60, Image_Toys_60x60) ;		// ?????

    HAL_Delay(2000);
}
/*************************************************************************************************
*	?? ?? ??:	LCD_Test_Direction
*
*	????????:	???????????
*************************************************************************************************/
void  LCD_Test_Direction(void)
{
    LCD_SetDirection(Direction_V);
    LCD_SetBackColor(LCD_BLACK); 			//	????????
    LCD_Clear(); 								// ????
    LCD_SetTextFont(&CH_Font12);
    LCD_SetColor( 0xffDFF9FB);
    LCD_DisplayText(5,10,"Direction_V");
    LCD_SetColor( 0xffF6E58D);
    LCD_DrawImage( 10,50, 60, 60, Image_Android_60x60) ;	   // ?????
    LCD_SetTextFont(&CH_Font24);
    LCD_SetColor( 0xff9DD3A8);
    LCD_DisplayText(16,112,"????");
    LCD_DisplayText(16,136,"???");
    HAL_Delay(1000);	// ???

    LCD_SetDirection(Direction_H);
    LCD_SetBackColor(LCD_BLACK); 			//	????????
    LCD_Clear(); 								// ????
    LCD_SetTextFont(&CH_Font16);
    LCD_SetColor( 0xffDFF9FB);
    LCD_DisplayText(20,0,"Direction_H");
    LCD_SetColor( 0xffF6E58D);
    LCD_DrawImage( 30,20, 60, 60, Image_Android_60x60) ;	   // ?????
    LCD_SetTextFont(&CH_Font24);
    LCD_SetColor( 0xff9DD3A8);
    LCD_DisplayText(100,16,"????");
    LCD_DisplayText(100,40,"???");
    HAL_Delay(1000);	// ???

    LCD_SetDirection(Direction_V_Flip);
    LCD_SetBackColor(LCD_BLACK); 			//	????????
    LCD_Clear(); 								// ????
    LCD_SetTextFont(&CH_Font16);
    LCD_SetColor( 0xffDFF9FB);
    LCD_DisplayText(20,10,"_V_Flip");
    LCD_SetColor( 0xffF6E58D);
    LCD_DrawImage( 10,50, 60, 60, Image_Android_60x60) ;	   // ?????
    LCD_SetTextFont(&CH_Font24);
    LCD_SetColor( 0xff9DD3A8);
    LCD_DisplayText(16,112,"????");
    LCD_DisplayText(16,136,"???");
    HAL_Delay(1000);	// ???

    LCD_SetDirection(Direction_H_Flip);
    LCD_SetBackColor(LCD_BLACK); 			//	????????
    LCD_Clear(); 								// ????
    LCD_SetTextFont(&CH_Font16);
    LCD_SetColor( 0xffDFF9FB);
    LCD_DisplayText(20,0,"Direction_H_Flip");
    LCD_SetColor( 0xffF6E58D);
    LCD_DrawImage( 30,20, 60, 60, Image_Android_60x60) ;	   // ?????
    LCD_SetTextFont(&CH_Font24);
    LCD_SetColor( 0xff9DD3A8);
    LCD_DisplayText(100,16,"????");
    LCD_DisplayText(100,40,"???");
    HAL_Delay(1000);	// ???

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
