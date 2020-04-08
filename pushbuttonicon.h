#ifndef PUSHBUTTONICON_H
#define PUSHBUTTONICON_H

#endif // PUSHBUTTONICON_H

#include <QPushButton>

class PushButtonIcon : public QPushButton
{
public:
    explicit PushButtonIcon(QWidget* parent = nullptr);
    virtual ~PushButtonIcon();

    void setPixmap(const QPixmap& pixmap);

    virtual QSize sizeHint() const override;

protected:
    virtual void paintEvent(QPaintEvent *) override;

private:
    QPixmap m_pixmap;
};
