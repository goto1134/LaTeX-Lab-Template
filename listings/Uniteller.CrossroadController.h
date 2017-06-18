// Uniteller.CrossroadController

// Данный файл был сгенерирован автоматически! Его ручное изменение запрещено правилами
// процесса разработки. При необходимости изменения следует исправить протокол в формате UniText,
// расположенный в файле protocol.utx, и затем повторить этап генерации заголовочного файла по декларативному описанию.

#pragma once
#include "kernel/protocolwrapper.h"

using namespace Uniteller::Framework::Kernel;
namespace Uniteller
{
  namespace CrossroadController
  {
    namespace Protocol
    {

      BEGIN_PROTOCOL(101, 1)

        //Структуры
        #pragma region Messages and wrappers

        //Сообщения
        // Обнаружена неполадка.
        BEGIN_MESSAGE(ProblemDetected,1,0)
          /// <summary>
          /// Инициализация сообщений
          /// </summary>
          void InitializeMessage()
          {
          }
        END_MESSAGE(); // ProblemDetected


        BEGIN_WRAPPER()
          /// <summary>
          /// Обнаружена неполадка.
          /// </summary>
          void ProblemDetected() const
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::ProblemDetected);
          }

        END_WRAPPER();

        BEGIN_IMPLEMENTATION()
          /// <summary>
          /// Отправка события ProblemDetected по адресу
          /// </summary>
          void SendProblemDetected(address target)
          {
            m_RequestDispatcher->SendEvent(target, G1::Codes::ProblemDetected);
          }
          /// <summary>
          /// Отправка события ProblemDetected самому себе
          /// </summary>
          void RaiseProblemDetected()
          {
            m_RequestDispatcher->SendEvent(m_sModuleId.c_str(), G1::Codes::ProblemDetected);
          }

        END_IMPLEMENTATION();

        #pragma endregion
      END_PROTOCOL()

      } // пространство имен Protocol
    } // пространство имен CrossroadController
  } // пространство имен Uniteller
