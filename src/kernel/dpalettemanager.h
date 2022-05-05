#ifndef DPALETTEMANAGER_H
#define DPALETTEMANAGER_H
#include <QColor>
#include <DConfig>
#include <QPalette>
#include <DPalette>

DGUI_USE_NAMESPACE
DCORE_USE_NAMESPACE

class DPaletteManager {
public:
    static DPaletteManager *instance(){
        static DPaletteManager *palette = new DPaletteManager;
        return palette;
    }

    QColor lightQpalette(const QPalette::ColorRole &role);
    QColor darkQpalette(const QPalette::ColorRole &role);
    QColor lightDpalette(const DPalette::ColorType &type);
    QColor darkDpalette(const DPalette::ColorType &type);

    QColor * qLightColor();
    QColor * qDarkColor();
    QColor * dLightColor();
    QColor * dDarkColor();

private:
    DPaletteManager();
    ~DPaletteManager();

    QColor getDefaultQColor(const QPalette::ColorRole &role, bool isDark);
    QColor getDefaultDColor(const DPalette::ColorType &type, bool isDark);

    QString getColorFromDConfig(DConfig &config, const QPalette::ColorRole &role);
    QString getColorFromDConfig(DConfig &config, const DPalette::ColorType &type);

    QColor colorStr2QColor(const QString &colorStr);

    std::array<QColor, QPalette::NColorRoles> m_lightQpalette;
    std::array<QColor, QPalette::NColorRoles> m_darkQpalette;
    std::array<QColor, DPalette::NColorRoles> m_lightDpalette;
    std::array<QColor, DPalette::NColorRoles> m_darkDpalette;
};

#define qPaletteColor(T, P) DPaletteManager::instance()->T##Qpalette(P)
#define dPaletteColor(T, P) DPaletteManager::instance()->T##Dpalette(P)

#define qColorData(T) DPaletteManager::instance()->q##T##Color()
#define dColorData(T) DPaletteManager::instance()->d##T##Color()

#endif//DPALETTEMANAGER_H
