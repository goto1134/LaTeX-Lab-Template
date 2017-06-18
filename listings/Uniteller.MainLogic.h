// Uniteller.MainLogic

// Данный файл был сгенерирован автоматически! Его ручное изменение запрещено правилами
// процесса разработки. При необходимости изменения следует исправить протокол в формате UniText,
// расположенный в файле protocol.utx, и затем повторить этап генерации заголовочного файла по декларативному описанию.

#pragma once
#include "kernel/protocolwrapper.h"

using namespace Uniteller::Framework::Kernel;
namespace Uniteller
{
  namespace MainLogic
  {
    namespace Protocol
    {

      BEGIN_PROTOCOL(101, 1)

        //Структуры
        #pragma region Messages and wrappers

        //Сообщения
        // Выгрузить управляющую логику
        BEGIN_MESSAGE(Shutdown,2,0)
          /// <summary>
          /// Инициализация сообщений
          /// </summary>
          void InitializeMessage()
          {
          }
        END_MESSAGE(); // Shutdown

        // Включить цикл работы светофора
        BEGIN_MESSAGE(Start,1,0)
          /// <summary>
          /// Инициализация сообщений
          /// </summary>
          void InitializeMessage()
          {
          }
        END_MESSAGE(); // Start


        BEGIN_WRAPPER()
          /// <summary>
          /// Выгрузить управляющую логику
          /// </summary>
          void Shutdown() const
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Shutdown);
          }

          /// <summary>
          /// Включить цикл работы светофора
          /// </summary>
          void Start() const
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Start);
          }

        END_WRAPPER();

        BEGIN_IMPLEMENTATION()
          /// <summary>
          /// Отправка события Shutdown по адресу
          /// </summary>
          void SendShutdown(address target)
          {
            m_RequestDispatcher->SendEvent(target, G1::Codes::Shutdown);
          }
          /// <summary>
          /// Отправка события Shutdown самому себе
          /// </summary>
          void RaiseShutdown()
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Shutdown);
          }

          /// <summary>
          /// Отправка события Start по адресу
          /// </summary>
          void SendStart(address target)
          {
            m_RequestDispatcher->SendEvent(target, G1::Codes::Start);
          }
          /// <summary>
          /// Отправка события Start самому себе
          /// </summary>
          void RaiseStart()
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::Start);
          }

        END_IMPLEMENTATION();

        #pragma endregion
      END_PROTOCOL()

      } // пространство имен Protocol
    } // пространство имен MainLogic
  } // пространство имен Uniteller
