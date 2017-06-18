// Uniteller.DeviceController

// Данный файл был сгенерирован автоматически! Его ручное изменение запрещено правилами
// процесса разработки. При необходимости изменения следует исправить протокол в формате UniText,
// расположенный в файле protocol.utx, и затем повторить этап генерации заголовочного файла по декларативному описанию.

#pragma once
#include "kernel/protocolwrapper.h"

using namespace Uniteller::Framework::Kernel;
namespace Uniteller
{
  namespace DeviceController
  {
    namespace Protocol
    {

      BEGIN_PROTOCOL(110, 1)

        #pragma region Enumerations
        /// <summary>
        /// Цвет светофора
        /// </summary>
        enum class ColorType
        {
          Green = 3, // - Зеленый цвет
          Red = 1, // - Красный цвет
          Yellow = 2 // - Желтый цвет
        };

        /// <summary>
        /// Валидатор корректности значения для перечислимого типа ColorType
        /// </summary>
        inline bool IsValidColorTypeValue(const int value)
        {
          return ((value >= 1)&&(value < 4));
        }

        /// <summary>
        /// Следует использовать для преобразования числовых значений к перечислимому типу ColorType
        /// </summary>
        inline ColorType ConvertToColorType(const int value)
        {
          switch (value)
          {
            case 3:
              return ColorType::Green;
            case 1:
              return ColorType::Red;
            case 2:
              return ColorType::Yellow;
            default: throw KernelException("Невозможно преобразовать числовое значение %d к типу ColorType", value);
            }
        }

        #pragma endregion

        //Структуры
        #pragma region Messages and wrappers

        //Сообщения
        // Ошибка в работе контроллера (авария)
        BEGIN_MESSAGE(Fail,3,0)
          /// <summary>
          /// Инициализация сообщений
          /// </summary>
          void InitializeMessage()
          {
          }
        END_MESSAGE(); // Fail

        // Установить новый сигнал
        BEGIN_MESSAGE(SetLight,1,1)
          /// <summary>
          /// Инициализация сообщений
          /// </summary>
          void InitializeMessage()
          {
          }
          // - Требуемый цвет сигнала
          ENUM(0, ColorType, Color);
        END_MESSAGE(); // SetLight

        // Команда контроллеру отработана
        BEGIN_MESSAGE(Success,2,0)
          /// <summary>
          /// Инициализация сообщений
          /// </summary>
          void InitializeMessage()
          {
          }
        END_MESSAGE(); // Success


        BEGIN_WRAPPER()
          /// <summary>
          /// Ошибка в работе контроллера (авария)
          /// </summary>
          void Fail() const
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Fail);
          }

          /// <summary>
          /// Установить новый сигнал
          /// </summary>
          /// <param name="color">- Требуемый цвет сигнала</param>
          void SetLight(ColorType color) const
          {
            G1::SetLight cmd;
            cmd.SetColor(color);
            m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
          }

          /// <summary>
          /// Команда контроллеру отработана
          /// </summary>
          void Success() const
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Success);
          }

        END_WRAPPER();

        BEGIN_IMPLEMENTATION()
          /// <summary>
          /// Отправка события Fail по адресу
          /// </summary>
          void SendFail(address target)
          {
            m_RequestDispatcher->SendEvent(target, G1::Codes::Fail);
          }
          /// <summary>
          /// Отправка события Fail самому себе
          /// </summary>
          void RaiseFail()
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Fail);
          }

          /// <summary>
          /// Отправка события SetLight по адресу
          /// </summary>
          /// <param name="color">- Требуемый цвет сигнала</param>
          void SendSetLight(address target, ColorType color)
          {
            G1::SetLight cmd;
            cmd.SetColor(color);
            m_RequestDispatcher->SendMessage(target, cmd);
          }
          /// <summary>
          /// Отправка события SetLight самому себе
          /// </summary>
          /// <param name="color">- Требуемый цвет сигнала</param>
          void RaiseSetLight(ColorType color)
          {
            G1::SetLight cmd;
            cmd.SetColor(color);
            m_RequestDispatcher->SendMessage(m_sModuleId.c_str(), cmd);
          }

          /// <summary>
          /// Отправка события Success по адресу
          /// </summary>
          void SendSuccess(address target)
          {
            m_RequestDispatcher->SendEvent(target, G1::Codes::Success);
          }
          /// <summary>
          /// Отправка события Success самому себе
          /// </summary>
          void RaiseSuccess()
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Success);
          }

        END_IMPLEMENTATION();

        #pragma endregion
      END_PROTOCOL()

      } // пространство имен Protocol
    } // пространство имен DeviceController
  } // пространство имен Uniteller
#pragma region Macro
#ifdef USE_DEVICECONTROLLER_HELPERS
#define FAIL_IF(cond, code) if (cond) {\
                             m_Protocol.RaiseFail(Protocol::G1::DeviceControllerErrors::code);\
                             return;\
                           }
#endif
#pragma endregion
