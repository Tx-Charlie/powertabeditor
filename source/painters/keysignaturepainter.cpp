#include "keysignaturepainter.h"

#include "staffdata.h"
#include "../powertabdocument/keysignature.h"
#include "../musicfont.h"

#include <QMessageBox>
#include <QFont>
#include <QPainter>
#include <QVector>

KeySignaturePainter::KeySignaturePainter(const StaffData& staffInformation, const KeySignature& signature) :
        staffInfo(staffInformation),
        keySignature(signature)
{
    init();
}

void KeySignaturePainter::mousePressEvent(QGraphicsSceneMouseEvent *)
{
}

void KeySignaturePainter::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    QMessageBox message;
    message.setText("Key Signature");
    message.exec();
}

void KeySignaturePainter::mouseMoveEvent(QGraphicsSceneMouseEvent *)
{
}

QRectF KeySignaturePainter::boundingRect() const
{
    return QRectF(0, 0, keySignature.GetWidth(), staffInfo.getStdNotationStaffSize());
}

void KeySignaturePainter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    MusicFont musicFont;
    painter->setFont(musicFont.getFont());

    // draw the appropriate accidentals
    if (keySignature.UsesFlats())
    {
        drawAccidentals(flatPositions, MusicFont::AccidentalFlat, painter);
    }
    else
    {
        drawAccidentals(sharpPositions, MusicFont::AccidentalSharp, painter);
    }
}

void KeySignaturePainter::adjustHeightOffset(QVector<double>& lst)
{
    for (QVector<double>::iterator i = lst.begin(); i != lst.end(); ++i)
    {
        *i -= staffInfo.getTopStdNotationLine();
    }
}

void KeySignaturePainter::drawAccidentals(QVector<double>& positions, QChar accidental, QPainter* painter)
{
    for(int i = 0; i < keySignature.NumberOfAccidentals(); i++)
    {
        painter->drawText(i * 6, positions.at(i), accidental);
    }
}

void KeySignaturePainter::init()
{
    flatPositions.resize(7);
    sharpPositions.resize(7);

    // generate the positions for the key signature accidentals
    flatPositions.replace(0, staffInfo.getStdNotationLineHeight(3));
    flatPositions.replace(1, staffInfo.getStdNotationSpaceHeight(1));
    flatPositions.replace(2, staffInfo.getStdNotationSpaceHeight(3));
    flatPositions.replace(3, staffInfo.getStdNotationLineHeight(2));
    flatPositions.replace(4, staffInfo.getStdNotationLineHeight(4));
    flatPositions.replace(5, staffInfo.getStdNotationSpaceHeight(2));
    flatPositions.replace(6, staffInfo.getStdNotationSpaceHeight(4));

    sharpPositions.replace(0, staffInfo.getStdNotationLineHeight(1));
    sharpPositions.replace(1, staffInfo.getStdNotationSpaceHeight(2));
    sharpPositions.replace(2, staffInfo.getStdNotationSpaceHeight(0));
    sharpPositions.replace(3, staffInfo.getStdNotationLineHeight(2));
    sharpPositions.replace(4, staffInfo.getStdNotationSpaceHeight(3));
    sharpPositions.replace(5, staffInfo.getStdNotationSpaceHeight(1));
    sharpPositions.replace(6, staffInfo.getStdNotationLineHeight(3));

    adjustHeightOffset(flatPositions);
    adjustHeightOffset(sharpPositions);
}
