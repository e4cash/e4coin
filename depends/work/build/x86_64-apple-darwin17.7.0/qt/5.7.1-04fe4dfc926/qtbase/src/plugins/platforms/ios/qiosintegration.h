/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QPLATFORMINTEGRATION_UIKIT_H
#define QPLATFORMINTEGRATION_UIKIT_H

#include <qpa/qplatformintegration.h>
#include <qpa/qplatformnativeinterface.h>
#include <qpa/qwindowsysteminterface.h>

#include "qiosapplicationstate.h"
#include "qiosfileenginefactory.h"
#include "qiostextinputoverlay.h"

QT_BEGIN_NAMESPACE

class QIOSServices;

class QIOSIntegration : public QPlatformNativeInterface, public QPlatformIntegration
{
    Q_OBJECT
    Q_PROPERTY(bool debugWindowManagement READ debugWindowManagement WRITE setDebugWindowManagement);

public:
    QIOSIntegration();
    ~QIOSIntegration();

    bool hasCapability(Capability cap) const Q_DECL_OVERRIDE;

    QPlatformWindow *createPlatformWindow(QWindow *window) const Q_DECL_OVERRIDE;
    QPlatformBackingStore *createPlatformBackingStore(QWindow *window) const Q_DECL_OVERRIDE;

    QPlatformOpenGLContext *createPlatformOpenGLContext(QOpenGLContext *context) const Q_DECL_OVERRIDE;
    QPlatformOffscreenSurface *createPlatformOffscreenSurface(QOffscreenSurface *surface) const Q_DECL_OVERRIDE;

    QPlatformFontDatabase *fontDatabase() const Q_DECL_OVERRIDE;
    QPlatformClipboard *clipboard() const Q_DECL_OVERRIDE;
    QPlatformInputContext *inputContext() const Q_DECL_OVERRIDE;
    QPlatformServices *services() const Q_DECL_OVERRIDE;

    QVariant styleHint(StyleHint hint) const Q_DECL_OVERRIDE;

    QStringList themeNames() const Q_DECL_OVERRIDE;
    QPlatformTheme *createPlatformTheme(const QString &name) const Q_DECL_OVERRIDE;

    QAbstractEventDispatcher *createEventDispatcher() const Q_DECL_OVERRIDE;
    QPlatformNativeInterface *nativeInterface() const Q_DECL_OVERRIDE;

    QTouchDevice *touchDevice();
    QPlatformAccessibility *accessibility() const Q_DECL_OVERRIDE;

    // Called from Objective-C class QIOSScreenTracker, which can't be friended
    void addScreen(QPlatformScreen *screen) { screenAdded(screen); }
    void destroyScreen(QPlatformScreen *screen) { QPlatformIntegration::destroyScreen(screen); }

    void beep() const Q_DECL_OVERRIDE;

    static QIOSIntegration *instance();

    // -- QPlatformNativeInterface --

    void *nativeResourceForWindow(const QByteArray &resource, QWindow *window) Q_DECL_OVERRIDE;

    void setDebugWindowManagement(bool);
    bool debugWindowManagement() const;

private:
    QPlatformFontDatabase *m_fontDatabase;
    QPlatformClipboard *m_clipboard;
    QPlatformInputContext *m_inputContext;
    QTouchDevice *m_touchDevice;
    QIOSApplicationState m_applicationState;
    QIOSServices *m_platformServices;
    mutable QPlatformAccessibility *m_accessibility;
    QIOSFileEngineFactory m_fileEngineFactory;
    QIOSTextInputOverlay m_textInputOverlay;

    bool m_debugWindowManagement;
};

QT_END_NAMESPACE

#endif
