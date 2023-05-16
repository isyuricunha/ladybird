/*
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2022, Matthew Costa <ucosty@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "LocationEdit.h"
#include "WebContentView.h"
#include <Browser/History.h>
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QToolBar>
#include <QToolButton>
#include <QWidget>

class BrowserWindow;

class Tab final : public QWidget {
    Q_OBJECT
public:
    Tab(BrowserWindow* window, StringView webdriver_content_ipc_path, WebView::EnableCallgrindProfiling);

    WebContentView& view() { return *m_view; }

    enum class LoadType {
        Normal,
        HistoryNavigation,
    };
    void navigate(QString, LoadType = LoadType::Normal);

    void debug_request(DeprecatedString const& request, DeprecatedString const& argument);

    void update_reset_zoom_button();

public slots:
    void focus_location_editor();
    void location_edit_return_pressed();
    void page_title_changed(QString);
    void page_favicon_changed(QIcon);
    void back();
    void forward();
    void reload();

signals:
    void title_changed(int id, QString);
    void favicon_changed(int id, QIcon);

private:
    virtual void resizeEvent(QResizeEvent*) override;
    virtual bool event(QEvent*) override;

    void rerender_toolbar_icons();
    void update_hover_label();

    void open_link(URL const&);
    void open_link_in_new_tab(URL const&);
    void copy_link_url(URL const&);

    enum class ScreenshotType {
        Visible,
        Full,
    };
    ErrorOr<void> take_screenshot(ScreenshotType);

    QBoxLayout* m_layout;
    QToolBar* m_toolbar { nullptr };
    QToolButton* m_reset_zoom_button { nullptr };
    QAction* m_reset_zoom_button_action { nullptr };
    LocationEdit* m_location_edit { nullptr };
    WebContentView* m_view { nullptr };
    BrowserWindow* m_window { nullptr };
    Browser::History m_history;
    QString m_title;
    QLabel* m_hover_label { nullptr };

    OwnPtr<QMenu> m_page_context_menu;

    OwnPtr<QMenu> m_link_context_menu;
    URL m_link_context_menu_url;

    OwnPtr<QMenu> m_image_context_menu;
    Gfx::ShareableBitmap m_image_context_menu_bitmap;
    URL m_image_context_menu_url;

    OwnPtr<QMenu> m_video_context_menu;
    OwnPtr<QIcon> m_video_context_menu_play_icon;
    OwnPtr<QIcon> m_video_context_menu_pause_icon;
    OwnPtr<QAction> m_video_context_menu_play_pause_action;
    OwnPtr<QAction> m_video_context_menu_controls_action;
    OwnPtr<QAction> m_video_context_menu_loop_action;
    URL m_video_context_menu_url;

    int tab_index();

    bool m_is_history_navigation { false };
};
