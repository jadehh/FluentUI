/**
# @File     : FluHotkey.cpp
# @Author   : jade
# @Date     : 2025/8/18 20:34
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : FluHotkey.cpp
*/
//
#include "include/FluHotkey.h"
#include "QGuiApplication"

FluHotkey::FluHotkey(QObject *parent) : QObject{parent} {
    _sequence = "";
    _isRegistered = false;
    connect(this, &FluHotkey::sequenceChanged, this, [=] {
        if (_hotkey) {
            delete _hotkey;
            _hotkey = nullptr;
        }
        _hotkey = new QHotkey(QKeySequence(_sequence), true, qApp);
        this->isRegistered(_hotkey->isRegistered());
        connect(_hotkey, &QHotkey::activated, qApp, [=]() { Q_EMIT this->activated(); });
        connect(_hotkey, &QHotkey::registeredChanged, qApp,
                         [=]() { this->isRegistered(_hotkey->isRegistered()); });
    });
}

FluHotkey::~FluHotkey() {
    if (_hotkey) {
        delete _hotkey;
        _hotkey = nullptr;
    }
}
