#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "system.h"
#include "odometry.h"
#include "can.h"
#include "sides.h"
#include "usart.h"

char driveByGreen(void)
{
	_delay_ms(4500);
	servo_position(190);
	
	return 0;
}
char detectEnemyGreen(void)
{
	if(GPIO_PinRead(forwardLeftSensor) == 1 || GPIO_PinRead(forwardRightSensor) == 1)
	{
		
	}
	return 0;
	if(GPIO_PinRead(backwardLeftSensor) == 1 || GPIO_PinRead(backwardRightSensor) == 1)
	{
		
	}
	return 0;
}


/*************************************************************************************************************************************************************************************
											 					POZICIJE,BRZINE,SMEROVI I DETEKCIJE ZA ZELENU STRANU
*************************************************************************************************************************************************************************************/
const moveOnDirectionFields greenSideTacticOnePositions[TACTIC_ONE_POSITION_COUNT] =
{
	{-220,90,detectEnemyGreen},//ide do pola stola							//1
	{-750,40,driveByGreen}
};




/*************************************************************************************************************************************************************************************
																				ZELENA STRANA
*************************************************************************************************************************************************************************************/
void greenSide(void)
{
	position startingPosition;
	unsigned char currentPosition = 0, nextPosition = 0, odometryStatus;
	unsigned char activeState = TACTIC_ONE;
	
	startingPosition.x = 0;
	startingPosition.y = 0;
	startingPosition.angle = 0;
	setPosition(startingPosition);
	
	while (1)
	{
		switch(activeState)
		{
			case TACTIC_ONE:
			for (currentPosition = nextPosition; currentPosition < TACTIC_ONE_POSITION_COUNT; currentPosition++)
			{
				// mozda ubaciti if-else sa akcijama tipa regularno- kretanje, i alternativno- sta god
				odometryStatus = moveOnDirection(greenSideTacticOnePositions[currentPosition].distance, greenSideTacticOnePositions[currentPosition].speed, greenSideTacticOnePositions[currentPosition].detectionCallback);
				
				if(odometryStatus == ODOMETRY_FAIL)
				{

				}
				else if(odometryStatus == ODOMETRY_STUCK)
				{
					
				}
				if(currentPosition == 0)
				{
					_delay_ms(1000);
					rotate(-79,50,NULL);//rotira se za stepenice
					_delay_ms(1000);
				}
				else if(currentPosition == 1)
				{
					_delay_ms(1000);
					rotate(-90,40,NULL);//gojkovic reko da stavim :D (samo da bolje izgleda)
					while(1);
				}			
			}//end for
			break;
		}
	}//end while(1)
	
	
}