#pragma once

#include "kernel/systemobject.h"
#include "kernel/xregistrykey.h"

// Протоколы
#include "Uniteller.Framework.Kernel.h"
#include "Uniteller.Framework.Kernel.Host.h"
#include "Uniteller.CrossroadController.h"
#include "Uniteller.MainLogic.h"
#include "Uniteller.DeviceController.h"

using namespace Uniteller::Framework::Kernel;

namespace Uniteller
{
  namespace CrossroadController
  {

        /// <summary>
        /// Главный класс модуля
        /// </summary>
        class Machine : public SystemObject<Machine, ISystemObject>
        {
        public:
          // Карта обработчиков событий конечного автомата
          BEGIN_HANDLERS_MAP()

            REGISTER_HANDLER("Start", "Pause", Framework::Kernel::Protocol::G1::Codes::Start,  &Machine::StartHandler);

      		  REGISTER_HANDLER("Pause", "SwitchToGreen", MainLogic::Protocol::G1::Codes::Start, &Machine::CycleStartHandler);

      		  REGISTER_HANDLER("SwitchToGreen", "Green", DeviceController::Protocol::G1::Codes::Success, &Machine::ColorSetNormallyHandler);
      		  REGISTER_HANDLER("SwitchToRed", "Red", DeviceController::Protocol::G1::Codes::Success, &Machine::ColorSetNormallyHandler);
      		  REGISTER_HANDLER("SwitchToYellow", "Yellow", DeviceController::Protocol::G1::Codes::Success, &Machine::ColorSetNormallyHandler);

      		  REGISTER_HANDLER("Green", "SwitchToYellow", Framework::Kernel::Protocol::G1::Codes::TimeOut, &Machine::GreenTimeOutHandler);
      		  REGISTER_HANDLER("Red", "SwitchToGreen", Framework::Kernel::Protocol::G1::Codes::TimeOut, &Machine::RedTimeOutHandler);
      		  REGISTER_HANDLER("Yellow", "SwitchToRed", Framework::Kernel::Protocol::G1::Codes::TimeOut, &Machine::YellowTimeOutHandler);
      		  REGISTER_HANDLER("SwitchToGreen", "Pause", Framework::Kernel::Protocol::G1::Codes::TimeOut, &Machine::SetColourTimeOutHandler);
      		  REGISTER_HANDLER("SwitchToRed", "Pause", Framework::Kernel::Protocol::G1::Codes::TimeOut, &Machine::SetColourTimeOutHandler);
      		  REGISTER_HANDLER("SwitchToYellow", "Pause", Framework::Kernel::Protocol::G1::Codes::TimeOut, &Machine::SetColourTimeOutHandler);
      		  REGISTER_HANDLER("SwitchToGreen", "Pause", DeviceController::Protocol::G1::Codes::Fail, &Machine::SetColourFailHandler);
      		  REGISTER_HANDLER("SwitchToRed", "Pause", DeviceController::Protocol::G1::Codes::Fail, &Machine::SetColourFailHandler);
      		  REGISTER_HANDLER("SwitchToYellow", "Pause", DeviceController::Protocol::G1::Codes::Fail, &Machine::SetColourFailHandler);

    		    REGISTER_HANDLER("Pause", "End", Framework::Kernel::Protocol::G1::Codes::Stop, &Machine::StopHandler);
      			REGISTER_HANDLER("Pause", "End", MainLogic::Protocol::G1::Codes::Shutdown, &Machine::StopHandler1);
      			REGISTER_HANDLER("Yellow", "End", Framework::Kernel::Protocol::G1::Codes::Stop, &Machine::StopHandler);
      			REGISTER_HANDLER("Yellow", "End", MainLogic::Protocol::G1::Codes::Shutdown, &Machine::StopHandler1);
      			REGISTER_HANDLER("SwitchToYellow", "End", Framework::Kernel::Protocol::G1::Codes::Stop, &Machine::StopHandler);
      			REGISTER_HANDLER("SwitchToYellow", "End", MainLogic::Protocol::G1::Codes::Shutdown, &Machine::StopHandler1);
      			REGISTER_HANDLER("Green", "End", Framework::Kernel::Protocol::G1::Codes::Stop, &Machine::StopHandler);
      			REGISTER_HANDLER("Green", "End", MainLogic::Protocol::G1::Codes::Shutdown, &Machine::StopHandler1);
      			REGISTER_HANDLER("SwitchToGreen", "End", Framework::Kernel::Protocol::G1::Codes::Stop, &Machine::StopHandler);
      			REGISTER_HANDLER("SwitchToGreen", "End", MainLogic::Protocol::G1::Codes::Shutdown, &Machine::StopHandler1);
      			REGISTER_HANDLER("Red", "End", Framework::Kernel::Protocol::G1::Codes::Stop, &Machine::StopHandler);
      			REGISTER_HANDLER("Red", "End", MainLogic::Protocol::G1::Codes::Shutdown, &Machine::StopHandler1);
      			REGISTER_HANDLER("SwitchToRed", "End", Framework::Kernel::Protocol::G1::Codes::Stop, &Machine::StopHandler);
      			REGISTER_HANDLER("SwitchToRed", "End", MainLogic::Protocol::G1::Codes::Shutdown, &Machine::StopHandler1);
          END_HANDLERS_MAP()
        public:
          Machine(IKernelApi * api) : SystemObject<Machine, ISystemObject>("Uniteller.CrossroadController", api)
          {
          }
          ~Machine();
        private: // Используемые протоколы
          //USE_PROTOCOL(Uniteller::Framework::Kernel::Host, 1, Host);

          IMPLEMENT_PROTOCOL(Uniteller::CrossroadController, 1, Protocol);

          /// <summary>
          /// Карта точек соединения (по каким адресам располагаются те или иные протоколы)
          /// </summary>
          BEGIN_ENDPOINTS()
            PROTOCOL_ENDPOINT(Protocol, GetUnicalId());

            //m_Host.SetModuleId("master", this);
          END_ENDPOINTS()

        protected: // Обработчики событий автомата
          DECLARE_HANDLER(StartHandler, Framework::Kernel::Protocol::G1::Start);
    		  DECLARE_HANDLER(StopHandler, Framework::Kernel::Protocol::G1::Stop);
    		  DECLARE_HANDLER(StopHandler1, MainLogic::Protocol::G1::Shutdown);
    		  DECLARE_HANDLER(CycleStartHandler, MainLogic::Protocol::G1::Start);
    		  DECLARE_HANDLER(ColorSetNormallyHandler, DeviceController::Protocol::G1::Success);
    		  DECLARE_HANDLER(SetColourFailHandler, DeviceController::Protocol::G1::Fail);
    		  DECLARE_HANDLER(SetColourTimeOutHandler, Framework::Kernel::Protocol::G1::TimeOut);
    		  DECLARE_HANDLER(GreenTimeOutHandler, Framework::Kernel::Protocol::G1::TimeOut);
    		  DECLARE_HANDLER(RedTimeOutHandler, Framework::Kernel::Protocol::G1::TimeOut);
    		  DECLARE_HANDLER(YellowTimeOutHandler, Framework::Kernel::Protocol::G1::TimeOut);
          void MachineInitErrorHandlerSystem(IMessage * message);
          //DECLARE_HANDLER(IsExistsHandler, Protocol::G1::IsExists);
          //DECLARE_HANDLER(CleanUpHandler, Protocol::G1::CleanUp);


        private: // Закрытые данные
			Framework::Kernel::address deviceAddress;
			Framework::Kernel::address mainLogicAddress;

        private: // Закрытые методы
          /// <summary>
          /// Очищает ресурсы
          /// </summary>
          void Clear();

        };

  } // пространство имен ComponentBuilder
} // пространство имен Uniteller
