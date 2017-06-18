#include "machine.h"
#include "kernel/smartqipointer.h"
#include "kernel/utils.h"
#include "kernel/messagefilter.h"

#include "Uniteller.Framework.Kernel.Host.h"
//#include "CrossroadController.h"

#include <thread>

using namespace std;

namespace Uniteller
{
  namespace CrossroadController
  {

        Machine::~Machine()
        {
          Clear();
        }

        void Machine::Clear()
        {
          // Очищаем за собой
        }


#pragma region Обработчики сообщений
        void Machine::StartHandler(const Framework::Kernel::Protocol::G1::Start & message)
        {

        }

		void Machine::StopHandler(const Framework::Kernel::Protocol::G1::Stop & message)
		{

		}

		void Machine::StopHandler1(const MainLogic::Protocol::G1::Shutdown & message)
		{

		}

		void Machine::CycleStartHandler(const MainLogic::Protocol::G1::Start & message)
		{
			mainLogicAddress = message.GetSourceId();
			DeviceController::Protocol::G1::SetLight setLight;
			setLight.SetColor(DeviceController::Protocol::G1::ColorType::Green);
			SendMessage(deviceAddress, setLight);
		}

		void Machine::SetColourFailHandler(const DeviceController::Protocol::G1::Fail & message)
		{
			CrossroadController::Protocol::G1::ProblemDetected answer;
			SendMessage(mainLogicAddress, answer);
		}

		void Machine::SetColourTimeOutHandler(const Framework::Kernel::Protocol::G1::TimeOut & message)
		{
			CrossroadController::Protocol::G1::ProblemDetected answer;
			SendMessage(mainLogicAddress, answer);
		}

		void Machine::ColorSetNormallyHandler(const DeviceController::Protocol::G1::Success & message)
		{

		}

		void Machine::GreenTimeOutHandler(const Framework::Kernel::Protocol::G1::TimeOut & message)
		{
			DeviceController::Protocol::G1::SetLight setLight;
			setLight.SetColor(DeviceController::Protocol::G1::ColorType::Yellow);
			SendMessage(deviceAddress, setLight);
		}

		void Machine::RedTimeOutHandler(const Framework::Kernel::Protocol::G1::TimeOut & message)
		{
			DeviceController::Protocol::G1::SetLight setLight;
			setLight.SetColor(DeviceController::Protocol::G1::ColorType::Green);
			SendMessage(deviceAddress, setLight);
		}

		void Machine::YellowTimeOutHandler(const Framework::Kernel::Protocol::G1::TimeOut & message)
		{
			DeviceController::Protocol::G1::SetLight setLight;
			setLight.SetColor(DeviceController::Protocol::G1::ColorType::Red);
			SendMessage(deviceAddress, setLight);
		}




#pragma endregion


  } // пространство имен ComponentBuilder

} // пространство имен Uniteller
