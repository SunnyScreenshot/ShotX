#include "guiapplicationhelper.h"

#include <QColor>

GuiApplicationHelper::GuiApplicationHelper()
{

}

inline static int adjustColorValue(int base, qint8 increment, int max = 255)
{
    return increment > 0 ? (max - base) * increment / 100.0 + base
           : base * (1 + increment / 100.0);
}

/*!
 * \brief GuiApplicationHelper::adjustColor 调整颜色
 * \note \row 取值范围均为 -100 ~ 100 ,当三原色参数为-100时，颜色为黑色，参数为100时，颜色为白色.
 *            以透明度( alphaFloat )为例,当参数为负数时基础色的 alphaFloat 值减少，现象偏向透明, 参数为正数alphaFloat 值增加，现象偏不透明
 * \param base base 基础色
 * \param hueFloat 色调
 * \param saturationFloat 饱和度
 * \param lightnessFloat 亮度
 * \param redFloat 红色
 * \param greenFloat 绿色
 * \param blueFloat 蓝色
 * \param alphaFloat Alpha通道(透明度)
 * \return 经过调整的颜色
 */
QColor GuiApplicationHelper::adjustColor(const QColor &base, qint8 hueFloat, qint8 saturationFloat, qint8 lightnessFloat, qint8 redFloat, qint8 greenFloat, qint8 blueFloat, qint8 alphaFloat)
{
    // 按HSL格式调整
    int H, S, L, A;
    base.getHsl(&H, &S, &L, &A);

    H = H > 0 ? adjustColorValue(H, hueFloat, 359) : H;
    S = adjustColorValue(S, saturationFloat);
    L = adjustColorValue(L, lightnessFloat);
    A = adjustColorValue(A, alphaFloat);

    QColor new_color = QColor::fromHsl(H, S, L, A);

    // 按RGB格式调整
    int R, G, B;
    new_color.getRgb(&R, &G, &B);

    R = adjustColorValue(R, redFloat);
    G = adjustColorValue(G, greenFloat);
    B = adjustColorValue(B, blueFloat);

    new_color.setRgb(R, G, B, A);

    return new_color;
}
