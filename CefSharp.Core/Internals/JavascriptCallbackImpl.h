// Copyright � 2010-2015 The CefSharp Authors. All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.

#pragma once

#include "include/cef_base.h"
#include "include/cef_app.h"

#include "CefSharpBrowserWrapper.h"

using namespace System;
using namespace System::Threading::Tasks;

namespace CefSharp
{
    namespace Internals
    {
        ref class JavascriptCallbackImpl : public IJavascriptCallback
        {
        private:
            WeakReference^ _browserWrapper;
            JavascriptCallback^ _callback;
            PendingTaskRepository<JavascriptResponse^>^ _pendingTasks;
            bool _disposed;

            CefRefPtr<CefProcessMessage> CreateCallMessage(int64 doneCallbackId, array<Object^>^ parameters);
            CefRefPtr<CefProcessMessage> CreateDestroyMessage();
            CefSharpBrowserWrapper^ GetBrowser();
            void DisposedGuard();
        public:
            JavascriptCallbackImpl(JavascriptCallback^ callback, PendingTaskRepository<JavascriptResponse^>^ pendingTasks, WeakReference^ browser);

            virtual Task<JavascriptResponse^>^ ExecuteAsync(array<Object^>^ parameters);

            ~JavascriptCallbackImpl() { this->!JavascriptCallbackImpl(); }
            !JavascriptCallbackImpl();
        };
    }
}