#include "WBTrapWebPageContent.h"

#include "core/UBApplication.h"
#include "core/UBApplicationController.h"
#include "gui/UBMainWindow.h"

WBTrapWebPageContentWindow::WBTrapWebPageContentWindow(QObject *controller, QWidget *parent)
    : QDialog(parent)
    , mController(controller)
{
    setModal(true);
    resize(800, 600);
    setObjectName("WBTrapWebPageContentWindow");
    setStyleSheet("QWidget#WBTrapWebPageContentWindow{background-color: rgb(225,225,225)");

    mTrapApplicationVLayout = new QVBoxLayout();
    mTrapApplicationVLayout->setSpacing(0);
    mTrapApplicationVLayout->setContentsMargins(1,1,1,1);
    setLayout(mTrapApplicationVLayout);

    mTrapApplicationHLayout = new QHBoxLayout(this);
    mTrapApplicationHLayout->setContentsMargins(0,0,0,0);
    mTrapApplicationHLayout->setSpacing(0);

    QList<QLabel *> buttonLabels;

    QToolButton *buttonWebTrapToLibrary = new QToolButton();
    buttonWebTrapToLibrary->setDefaultAction(UBApplication::mainWindow->actionWebTrapToLibrary);
    buttonLabels << new QLabel(tr("Download to\nlibrary"));
    mTrapButtons << buttonWebTrapToLibrary;

    QToolButton *buttonWebTrapToCurrentPage = new QToolButton();
    buttonWebTrapToCurrentPage->setDefaultAction(UBApplication::mainWindow->actionWebTrapToCurrentPage);
    buttonLabels << new QLabel(tr("Download to\ncurrent page"));
    mTrapButtons << buttonWebTrapToCurrentPage;

    QToolButton *buttonWebTrapLinkToLibrary = new QToolButton();
    buttonWebTrapLinkToLibrary->setDefaultAction(UBApplication::mainWindow->actionWebTrapLinkToLibrary);
    buttonLabels << new QLabel(tr("Add link to\nlibrary"));
    mTrapButtons << buttonWebTrapLinkToLibrary;

    QToolButton *buttonWebTrapLinkToPage = new QToolButton();
    buttonWebTrapLinkToPage->setDefaultAction(UBApplication::mainWindow->actionWebTrapLinkToPage);
    buttonLabels << new QLabel(tr("Add link to\ncurrent page"));
    mTrapButtons << buttonWebTrapLinkToPage;

    QString buttonStileSheet("QToolButton#WBWebTrapToolButton{background-color: rgb(127, 127, 127, 20%)}");
   
    QWidget *buttonsLayoutWidget = new QWidget();
    buttonsLayoutWidget->setObjectName("WBWebTrapButtonsLayoutWidget");
    buttonsLayoutWidget->setStyleSheet("QWidget#WBWebTrapButtonsLayoutWidget{border: 2px solid #999999; border-top-style: none; border-right-style: none}");
    QVBoxLayout *buttonsLayout = new QVBoxLayout();
    buttonsLayoutWidget->setLayout(buttonsLayout);
    buttonsLayout->setAlignment(Qt::AlignTop);
    buttonsLayout->setContentsMargins(7,3,3,7);
        
    for (int i = 0; i < 4; i++)
    {
        QToolButton *button = mTrapButtons.at(i);

        button->setObjectName("WBWebTrapToolButton");
        button->setToolButtonStyle(Qt::ToolButtonIconOnly);
        button->setIconSize(QSize(64, 64));
        button->setMinimumSize(QSize(64,64));
        button->setMaximumSize(QSize(64,64)); 
        button->setStyleSheet(buttonStileSheet);
        button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        button->defaultAction()->setEnabled(false);

        QLabel *buttonLabel = buttonLabels.at(i);
        buttonLabel->setMaximumWidth(64);
        buttonLabel->setTextFormat(Qt::PlainText);
        buttonLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        buttonLabel->setAlignment(Qt::AlignHCenter);

        QVBoxLayout *currentButtonWithLabelWayout = new QVBoxLayout();
        currentButtonWithLabelWayout->setAlignment(Qt::AlignVCenter);
        currentButtonWithLabelWayout->setContentsMargins(1,0,1,0);
        currentButtonWithLabelWayout->addWidget(button);

        currentButtonWithLabelWayout->addWidget(buttonLabel);
        currentButtonWithLabelWayout->setSpacing(0);
        buttonsLayout->addLayout(currentButtonWithLabelWayout);        
    }

    QWidget *trapContentLayoutWidget = new QWidget();
    trapContentLayoutWidget->setObjectName("WBWebTrapPreviewWidget");
    trapContentLayoutWidget->setStyleSheet("QWidget#WBWebTrapPreviewWidget{border: 2px solid #999999; border-left-style: none; border-top-style: none; border-right-style: none}");
    QVBoxLayout *trapContentVLayout = new QVBoxLayout();
    trapContentVLayout->setContentsMargins(1,3,7,7);
    trapContentVLayout->setSpacing(1);
    trapContentLayoutWidget->setLayout(trapContentVLayout);

    trapContentLayoutWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mSelectContentLayout = new QHBoxLayout();
    trapContentVLayout->addLayout(mSelectContentLayout);

    mSelectContentLabel = new QLabel(tr("Select content to trap:"));
    mSelectContentLayout->addWidget(mSelectContentLabel);

    mSelectContentCombobox = new QComboBox(this);
    mSelectContentLayout->addWidget(mSelectContentCombobox);

    mSelectContentCombobox->setMaxVisibleItems(15);
    mSelectContentCombobox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    mTrapContentPreview = new WBWebView();
    trapContentVLayout->addWidget(mTrapContentPreview);

    mTrapContentPreview->setMinimumSize(QSize(320, 240));
    mTrapContentPreview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mApplicationNameLayout = new QHBoxLayout();
    trapContentVLayout->addLayout(mApplicationNameLayout);

    mApplicationNameLabel = new QLabel(tr("Application name"));
    mApplicationNameLayout->addWidget(mApplicationNameLabel);

    mApplicationNameEdit = new QLineEdit();
    mApplicationNameLayout->addWidget(mApplicationNameEdit);

    mTrapApplicationHLayout->addWidget(trapContentLayoutWidget);
    mTrapApplicationHLayout->addWidget(buttonsLayoutWidget);

    mTrapApplicationVLayout->addLayout(mTrapApplicationHLayout);
    QLabel *infoLabel1 = new QLabel(tr("Restriction and disclaimer. "));
    QLabel *infoLabel2 = new QLabel(tr("This feature is developed to work on the most common web pages."));
    QLabel *infoLabel3 = new QLabel(tr("Please respect copyrights for creating links or trapping content from the web."));


    infoLabel1->setAlignment(Qt::AlignHCenter);
    infoLabel2->setAlignment(Qt::AlignHCenter);
    infoLabel3->setAlignment(Qt::AlignHCenter);

    mTrapApplicationVLayout->addWidget(infoLabel1);
    mTrapApplicationVLayout->addWidget(infoLabel2);
    mTrapApplicationVLayout->addWidget(infoLabel3);

    connect(mTrapContentPreview, SIGNAL(pixmapCaptured(const QPixmap&, bool)), UBApplication::applicationController, SLOT(addCapturedPixmap(const QPixmap &, bool)));
    connect(mTrapContentPreview, SIGNAL(embedCodeCaptured(const QString&)), UBApplication::applicationController, SLOT(addCapturedEmbedCode(const QString&)));

    connect(mSelectContentCombobox, SIGNAL(currentIndexChanged(int)), mController, SLOT(selectHtmlObject(int)));
    connect(mApplicationNameEdit, SIGNAL(textChanged(const QString &)), mController, SLOT(text_Changed(const QString &)));
    connect(mApplicationNameEdit, SIGNAL(textEdited(const QString &)), mController, SLOT(text_Edited(const QString &)));

    connect(UBApplication::mainWindow->actionWebTrapToCurrentPage, SIGNAL(triggered()), mController, SLOT(addItemToBoard()));
    connect(UBApplication::mainWindow->actionWebTrapToLibrary, SIGNAL(triggered()), mController, SLOT(addItemToLibrary()));
    connect(UBApplication::mainWindow->actionWebTrapLinkToPage, SIGNAL(triggered()), mController, SLOT(addLinkToBoard()));
    connect(UBApplication::mainWindow->actionWebTrapLinkToLibrary, SIGNAL(triggered()), mController, SLOT(addLinkToLibrary()));
}

WBTrapWebPageContentWindow::~WBTrapWebPageContentWindow()
{

}

void WBTrapWebPageContentWindow::setUrl(const QUrl &url)
{
    mTrapContentPreview->setUrl(url);
}

void WBTrapWebPageContentWindow::setReadyForTrap(bool bReady)
{
    foreach (QToolButton *button, mTrapButtons)
    {
        button->defaultAction()->setEnabled(bReady);
    }
}

