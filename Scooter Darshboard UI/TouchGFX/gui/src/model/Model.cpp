#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "stm32f7xx_hal.h"

extern volatile uint16_t adcval;

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
modelListener->updateGuage(adcval*200/4095);
}
