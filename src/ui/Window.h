#ifndef OTTER_WINDOW_H
#define OTTER_WINDOW_H

#include "../core/SessionsManager.h"

#include <QtCore/QUrl>
#include <QtGui/QIcon>
#include <QtPrintSupport/QPrinter>
#include <QtWidgets/QWidget>
#include <QtWidgets/QUndoStack>

namespace Otter
{

namespace Ui
{
	class Window;
}

enum WindowAction
{
	NoAction = 0,
	OpenLinkAction,
	OpenLinkInThisTabAction,
	OpenLinkInNewTabAction,
	OpenLinkInNewTabBackgroundAction,
	OpenLinkInNewWindowAction,
	OpenLinkInNewWindowBackgroundAction,
	CopyLinkToClipboardAction,
	SaveLinkToDiskAction,
	SaveLinkToDownloadsAction,
	OpenFrameInThisTabAction,
	OpenFrameInNewTabAction,
	OpenFrameInNewTabBackgroundAction,
	CopyFrameLinkToClipboardAction,
	OpenImageInNewTabAction,
	SaveImageToDiskAction,
	CopyImageToClipboardAction,
	CopyImageUrlToClipboardAction,
	ImagePropertiesAction,
	GoBackAction,
	GoForwardAction,
	RewindBackAction,
	RewindForwardAction,
	StopAction,
	StopScheduledPageRefreshAction,
	ReloadAction,
	ReloadOrStopAction,
	ReloadFrameAction,
	ReloadAndBypassCacheAction,
	ReloadTimeAction,
	CutAction,
	CopyAction,
	PasteAction,
	DeleteAction,
	SelectAllAction,
	ClearAllAction,
	SpellCheckAction,
	UndoAction,
	RedoAction,
	InspectPageAction,
	InspectElementAction,
	PrintAction,
	BookmarkAction,
	BookmarkLinkAction,
	CopyAddressAction,
	ViewSourceAction,
	ViewSourceFrameAction,
	ValidateAction,
	ContentBlockingAction,
	WebsitePreferencesAction,
	FullScreenAction,
	ZoomInAction,
	ZoomOutAction,
	ZoomOriginalAction,
	SearchAction,
	SearchMenuAction,
	OpenSelectionAsLinkAction,
	CreateSearchAction,
	FindAction,
	FindNextAction,
	FindPreviousAction,
	SaveMediaToDiskAction,
	CopyMediaUrlToClipboardAction,
	ToggleMediaControlsAction,
	ToggleMediaLoopAction,
	ToggleMediaPlayPauseAction,
	ToggleMediaMuteAction
};

class ContentsWidget;

class Window : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(QString title READ getTitle NOTIFY titleChanged)
	Q_PROPERTY(QString type READ getType)
	Q_PROPERTY(QUrl url READ getUrl WRITE setUrl NOTIFY urlChanged)
	Q_PROPERTY(QIcon icon READ getIcon NOTIFY iconChanged)
	Q_PROPERTY(QPixmap thumbnail READ getThumbnail)
	Q_PROPERTY(bool canClone READ canClone)
	Q_PROPERTY(bool isLoading READ isLoading NOTIFY loadingChanged)
	Q_PROPERTY(bool isPinned READ isPinned WRITE setPinned NOTIFY isPinnedChanged)
	Q_PROPERTY(bool isPrivate READ isPrivate)

public:
	explicit Window(bool privateWindow, ContentsWidget *widget, QWidget *parent = NULL);
	~Window();

	void close();
	Window* clone(QWidget *parent = NULL);
	ContentsWidget* getContentsWidget();
	QString getDefaultTextEncoding() const;
	QString getSearchEngine() const;
	QString getTitle() const;
	QLatin1String getType() const;
	QUrl getUrl() const;
	QIcon getIcon() const;
	QPixmap getThumbnail() const;
	bool canClone() const;
	bool isLoading() const;
	bool isPinned() const;
	bool isPrivate() const;

public slots:
	void search(const QString &query, const QString &engine);
	void setDefaultTextEncoding(const QString &encoding);
	void setSearchEngine(const QString &engine);
	void setUrl(const QUrl &url);
	void setPinned(bool pinned);

protected:
	void changeEvent(QEvent *event);
	void setContentsWidget(ContentsWidget *widget);

protected slots:
	void notifyRequestedCloseWindow();
	void notifyRequestedOpenUrl(const QUrl &url, bool background, bool newWindow);

private:
	ContentsWidget *m_contentsWidget;
	bool m_isPinned;
	Ui::Window *m_ui;

signals:
	void aboutToClose();
	void requestedCloseWindow(Window *window);
	void requestedOpenUrl(QUrl url, bool privateWindow = false, bool background = false, bool newWindow = false);
	void requestedAddBookmark(QUrl url, QString title);
	void requestedNewWindow(ContentsWidget *widget);
	void requestedSearch(QString query, QString search);
	void actionsChanged();
	void canZoomChanged(bool can);
	void statusMessageChanged(const QString &message, int timeout);
	void titleChanged(const QString &title);
	void urlChanged(const QUrl &url);
	void iconChanged(const QIcon &icon);
	void loadingChanged(bool loading);
	void zoomChanged(int zoom);
	void isPinnedChanged(bool pinned);
};

}

#endif
