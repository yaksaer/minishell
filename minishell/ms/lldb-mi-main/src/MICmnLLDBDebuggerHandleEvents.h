//===-- MICmnLLDBDebuggerHandleEvents.h -------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#pragma once

// Third party headers:
#include <type_traits>

// In-house headers:
#include "MICmnBase.h"
#include "MICmnMIValueList.h"
#include "MICmnMIValueTuple.h"
#include "MIUtilSingletonBase.h"
#include "lldb/API/SBEvent.h"

// Declarations:
class CMICmnLLDBDebugSessionInfo;
class CMICmnMIResultRecord;
class CMICmnStreamStdout;
class CMICmnMIOutOfBandRecord;

//++
//============================================================================
// Details: MI class to take LLDB SBEvent objects, filter them and form
//          MI Out-of-band records from the information inside the event object.
//          These records are then pushed to stdout.
//          A singleton class.
//--
class CMICmnLLDBDebuggerHandleEvents
    : public CMICmnBase,
      public MI::ISingleton<CMICmnLLDBDebuggerHandleEvents> {
  friend class MI::ISingleton<CMICmnLLDBDebuggerHandleEvents>;

  // Methods:
public:
  bool Initialize() override;
  bool Shutdown() override;
  //
  bool HandleEvent(const lldb::SBEvent &vEvent, bool &vrbHandledEvent);

  // Methods:
private:
  /* ctor */ CMICmnLLDBDebuggerHandleEvents();
  /* ctor */ CMICmnLLDBDebuggerHandleEvents(
      const CMICmnLLDBDebuggerHandleEvents &);
  void operator=(const CMICmnLLDBDebuggerHandleEvents &);
  //
  bool ChkForStateChanges();
  bool GetProcessStdout();
  bool GetProcessStderr();
  bool HandleEventSBBreakPoint(const lldb::SBEvent &vEvent);
  bool HandleEventSBWatchpoint(const lldb::SBEvent &vEvent);
  bool HandleEventSBBreakpointLocationsAdded(const lldb::SBEvent &vEvent);
  template <class T, class = std::enable_if_t<
                         std::is_same<T, lldb::SBBreakpoint>::value ||
                         std::is_same<T, lldb::SBWatchpoint>::value>>
  bool HandleEventStoppointCmn(T &vrStoppoint);
  template <class T, class = std::enable_if_t<
                         std::is_same<T, lldb::SBBreakpoint>::value ||
                         std::is_same<T, lldb::SBWatchpoint>::value>>
  bool HandleEventStoppointAdded(T &vrStoppoint);
  template <class T, class = std::enable_if_t<
                         std::is_same<T, lldb::SBBreakpoint>::value ||
                         std::is_same<T, lldb::SBWatchpoint>::value>>
  bool RemoveStoppointInfo(T &vrStoppoint);
  bool HandleEventSBProcess(const lldb::SBEvent &vEvent);
  bool HandleEventSBTarget(const lldb::SBEvent &vEvent);
  bool HandleEventSBThread(const lldb::SBEvent &vEvent);
  bool HandleEventSBThreadBitStackChanged(const lldb::SBEvent &vEvent);
  bool HandleEventSBThreadSuspended(const lldb::SBEvent &vEvent);
  bool HandleEventSBCommandInterpreter(const lldb::SBEvent &vEvent);
  bool HandleProcessEventBroadcastBitStateChanged(const lldb::SBEvent &vEvent);
  bool HandleProcessEventStateRunning();
  bool HandleProcessEventStateExited();
  bool HandleProcessEventStateStopped(const lldb::SBEvent &vrEvent,
                                      bool &vwrbShouldBrk);
  bool HandleProcessEventStopReasonTrace();
  bool HandleProcessEventStopReasonBreakpoint();
  bool HandleProcessEventStopReasonWatchpoint();
  bool HandleProcessEventStopSignal(const lldb::SBEvent &vrEvent);
  bool HandleProcessEventStopException();
  bool HandleProcessEventStateSuspended(const lldb::SBEvent &vEvent);
  bool HandleTargetEventBroadcastBitModulesLoaded(const lldb::SBEvent &vEvent);
  bool
  HandleTargetEventBroadcastBitModulesUnloaded(const lldb::SBEvent &vEvent);
  bool MiHelpGetModuleInfo(const lldb::SBModule &vModule,
                           const bool vbWithExtraFields,
                           CMICmnMIOutOfBandRecord &vwrMiOutOfBandRecord);
  bool MiHelpGetCurrentThreadFrame(CMICmnMIValueTuple &vwrMiValueTuple);
  bool MiResultRecordToStdout(const CMICmnMIResultRecord &vrMiResultRecord);
  bool
  MiOutOfBandRecordToStdout(const CMICmnMIOutOfBandRecord &vrMiResultRecord);
  bool MiStoppedAtBreakPoint(const MIuint64 vBreakpointId,
                             const lldb::SBBreakpoint &vBreakpoint);
  bool MiStoppedAtWatchpoint(lldb::SBWatchpoint &vrWatchpoint);
  bool TextToStdout(const CMIUtilString &vrTxt);
  bool TextToStderr(const CMIUtilString &vrTxt);
  bool UpdateSelectedThread();

  // Overridden:
private:
  // From CMICmnBase
  /* dtor */ ~CMICmnLLDBDebuggerHandleEvents() override;
  void InitializeSignals();
  bool m_bSignalsInitialized;
  MIuint64 m_SIGINT;
  MIuint64 m_SIGSTOP;
  MIuint64 m_SIGSEGV;
  MIuint64 m_SIGTRAP;
};
