#include "dpalettemanager.h"
#include <QMetaEnum>

#define IS_VALID_DCONFIG(D)     \
    if (!D.isValid()) {         \
        qWarning() << QString("DConfig is invalid, name:[%1], subpath[%2].").arg(D.name(), D.subpath()); \
    }

DPaletteManager::DPaletteManager()
{
    DConfig lightQPalette("org.deepin.dtkgui.light.qpalette");
    DConfig darkQPalette("org.deepin.dtkgui.dark.qpalette");
    DConfig lightDPalette("org.deepin.dtkgui.light.dpalette");
    DConfig darkDPalette("org.deepin.dtkgui.dark.dpalette");

    IS_VALID_DCONFIG(lightQPalette);
    IS_VALID_DCONFIG(darkQPalette);
    IS_VALID_DCONFIG(lightDPalette);
    IS_VALID_DCONFIG(darkDPalette);

    QColor colorLight, colorDark;
    for (int i = 0; i < QPalette::NColorRoles; i++) {
        colorLight = colorStr2QColor(getColorFromDConfig(lightQPalette, (QPalette::ColorRole)i));
        if (!colorLight.isValid()) {
            colorLight = getDefaultQColor((QPalette::ColorRole)i, false);
        }
        colorDark = colorStr2QColor(getColorFromDConfig(darkQPalette, (QPalette::ColorRole)i));
        if (!colorDark.isValid()) {
            colorDark = getDefaultQColor((QPalette::ColorRole)i, true);
        }
        m_darkQpalette[i] = colorDark;
        m_lightQpalette[i] = colorLight;
    }
    for (int i = 1; i < DPalette::NColorRoles; i++) {
        colorLight = colorStr2QColor(getColorFromDConfig(lightDPalette, (DPalette::ColorType)i));
        if (!colorLight.isValid()) {
            colorLight = getDefaultDColor((DPalette::ColorType)i, false);
        }
        colorDark = colorStr2QColor(getColorFromDConfig(darkDPalette, (DPalette::ColorType)i));
        if (!colorDark.isValid()) {
            colorDark = getDefaultDColor((DPalette::ColorType)i, true);
        }
        m_lightDpalette[i] = colorLight;
        m_darkDpalette[i] = colorDark;
    }
}

DPaletteManager::~DPaletteManager()
{
}

static QColor light_qpalette[QPalette::NColorRoles] {
    QColor("#414d68"),                  //WindowText
    QColor("#e5e5e5"),                  //Button
    QColor("#e6e6e6"),                  //Light
    QColor("#e5e5e5"),                  //Midlight
    QColor("#e3e3e3"),                  //Dark
    QColor("#e4e4e4"),                  //Mid
    QColor("#414d68"),                  //Text
    Qt::black,                          //BrightText
    QColor("#414d68"),                  //ButtonText
    Qt::white,                          //Base
    QColor("#f8f8f8"),                  //Window
    QColor(0, 0, 0, 0.05 * 255),        //Shadow
    QColor("#0081ff"),                  //Highlight
    Qt::white,                          //HighlightedText
    QColor("#0082fa"),                  //Link
    QColor("#ad4579"),                  //LinkVisited
    QColor(0, 0, 0, 0.03 * 255),        //AlternateBase
    Qt::white,                          //NoRole
    QColor(255, 255, 255, 0.8 * 255),   //ToolTipBase
    Qt::black                           //ToolTipText
};

static QColor dark_qpalette[QPalette::NColorRoles] {
    QColor("#c0c6d4"),                  //WindowText
    QColor("#444444"),                  //Button
    QColor("#484848"),                  //Light
    QColor("#474747"),                  //Midlight
    QColor("#414141"),                  //Dark
    QColor("#434343"),                  //Mid
    QColor("#c0c6d4"),                  //Text
    Qt::white,                          //BrightText
    QColor("#c0c6d4"),                  //ButtonText
    QColor("#282828"),                  //Base
    QColor("#252525"),                  //Window
    QColor(0, 0, 0, 0.05 * 255),        //Shadow
    QColor("#0081ff"),                  //Highlight
    QColor("#F1F6FF"),                  //HighlightedText
    QColor("#0082fa"),                  //Link
    QColor("#ad4579"),                  //LinkVisited
    QColor(0, 0, 0, 0.05 * 255),        //AlternateBase
    Qt::black,                          //NoRole
    QColor(45, 45, 45, 0.8 * 255),      //ToolTipBase
    QColor("#c0c6d4")                   //ToolTipText
};

static QColor light_dpalette[DPalette::NColorTypes] {
    QColor(),                           //NoType
    QColor(0, 0, 0, 255 * 0.03),        //ItemBackground
    QColor("#001A2E"),                  //TextTitle
    QColor("#526A7F"),                  //TextTips
    QColor("#FF5736"),                  //TextWarning
    Qt::white,                          //TextLively
    QColor("#0081FF"),                  //LightLively
    QColor("#0081FF"),                  //DarkLively
    QColor(0, 0, 0, 0.05 * 255),        //FrameBorder
    QColor(85, 85, 85, 0.4 * 255),      //PlaceholderText
    QColor(0, 0, 0, 0.1 * 255),         //FrameShadowBorder
    QColor(0, 0, 0, 0.1 * 255)          //ObviousBackground
};

static QColor dark_dpalette[DPalette::NColorTypes] {
    QColor(),                           //NoType
    QColor(255, 255, 255, 255 * 0.05),  //ItemBackground
    QColor("#C0C6D4"),                  //TextTitle
    QColor("#6D7C88"),                  //TextTips
    QColor("#9a2f2f"),                  //TextWarning
    Qt::white,                          //TextLively
    QColor("#0059d2"),                  //LightLively
    QColor("#0059d2"),                  //DarkLively
    QColor(255, 255, 255, 0.1 * 255),   //FrameBorder
    QColor(192, 198, 212, 0.4 * 255),   //PlaceholderText
    QColor(0, 0, 0, 0.8 * 255),         //FrameShadowBorder
    QColor(255, 255, 255, 0.1 * 255)    //ObviousBackground
};

QColor DPaletteManager::getDefaultQColor(const QPalette::ColorRole &role, bool isDark) {
    return isDark ? dark_qpalette[role] : light_qpalette[role];
}

QColor DPaletteManager::getDefaultDColor(const DPalette::ColorType &type, bool isDark) {
    return isDark ? dark_dpalette[type] : light_dpalette[type];
}

QString DPaletteManager::getColorFromDConfig(DConfig &config, const QPalette::ColorRole &role) {
    if (!config.isValid()) {
        return {};
    }
    const QString &key(QMetaEnum::fromType<QPalette::ColorRole>().valueToKey(role));
    return config.value(key).toString();
};

QString DPaletteManager::getColorFromDConfig(DConfig &config, const DPalette::ColorType &type) {
    if (!config.isValid()) {
        return {};
    }
    const QString &key(QMetaEnum::fromType<DPalette::ColorType>().valueToKey(type));
    return config.value(key).toString();
}

QColor DPaletteManager::colorStr2QColor(const QString &colorStr) {
    if (colorStr.startsWith("#")) {
        return QColor(colorStr);
    }
    auto rgba = colorStr.split(",");
    if (rgba.size() == 3) {
        return QColor(rgba.at(0).toInt(), rgba.at(1).toInt(), rgba.at(2).toInt());
    }
    if (rgba.size() == 4) {
        return QColor(rgba.at(0).toInt(), rgba.at(1).toInt(), rgba.at(2).toInt(), rgba.at(3).toInt());
    }
    return {};
}

QColor DPaletteManager::lightQpalette(const QPalette::ColorRole &role) {
    return m_lightQpalette.at(role);
}

QColor DPaletteManager::darkQpalette(const QPalette::ColorRole &role) {
    return m_darkQpalette.at(role);
}

QColor DPaletteManager::lightDpalette(const DPalette::ColorType &type) {
    return m_lightDpalette.at(type);
}

QColor DPaletteManager::darkDpalette(const DPalette::ColorType &type) {
    return m_darkDpalette.at(type);
}

QColor * DPaletteManager::qLightColor() {
    return m_lightQpalette.data();
}
QColor * DPaletteManager::qDarkColor() {
    return m_darkQpalette.data();
}
QColor * DPaletteManager::dLightColor() {
    return m_lightDpalette.data();
}
QColor * DPaletteManager::dDarkColor() {
    return m_darkDpalette.data();
}
