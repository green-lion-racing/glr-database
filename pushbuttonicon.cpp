#include "pushbuttonicon.h"

#include <QPainter>

PushButtonIcon::PushButtonIcon(QWidget* parent) : QPushButton(parent)
{
}

PushButtonIcon::~PushButtonIcon()
{
}

QSize PushButtonIcon::sizeHint() const
{
    const auto parentHint = QPushButton::sizeHint();
    // margin??
    return QSize(parentHint.width() + m_pixmap.width(), std::max(parentHint.height(), m_pixmap.height()));
}

void PushButtonIcon::setPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;
}

void PushButtonIcon::paintEvent(QPaintEvent* e)
{
    QPushButton::paintEvent(e);

    if (!m_pixmap.isNull()) {
        const int y = (height() - m_pixmap.height())/2;     // plus margin??
        const int x = ((width() - m_pixmap.width())/2);
        QPainter painter(this);
        painter.drawPixmap(x, y, m_pixmap);
    }
}
