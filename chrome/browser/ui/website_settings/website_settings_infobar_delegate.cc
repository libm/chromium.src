// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/website_settings/website_settings_infobar_delegate.h"

#include "base/logging.h"
#include "base/strings/utf_string_conversions.h"
#include "chrome/browser/infobars/infobar_service.h"
#include "content/public/browser/web_contents.h"
#include "grit/generated_resources.h"
#include "grit/theme_resources.h"
#include "ui/base/l10n/l10n_util.h"


// static
void WebsiteSettingsInfoBarDelegate::Create(InfoBarService* infobar_service) {
  infobar_service->AddInfoBar(scoped_ptr<InfoBarDelegate>(
      new WebsiteSettingsInfoBarDelegate(infobar_service)));
}

WebsiteSettingsInfoBarDelegate::WebsiteSettingsInfoBarDelegate(
    InfoBarService* infobar_service)
    : ConfirmInfoBarDelegate(infobar_service) {
}

WebsiteSettingsInfoBarDelegate::~WebsiteSettingsInfoBarDelegate() {
}

int WebsiteSettingsInfoBarDelegate::GetIconID() const {
  return IDR_INFOBAR_ALT_NAV_URL;
}

InfoBarDelegate::Type WebsiteSettingsInfoBarDelegate::GetInfoBarType() const {
  return PAGE_ACTION_TYPE;
}

string16 WebsiteSettingsInfoBarDelegate::GetMessageText() const {
  return l10n_util::GetStringUTF16(IDS_WEBSITE_SETTINGS_INFOBAR_TEXT);
}

int WebsiteSettingsInfoBarDelegate::GetButtons() const {
  return BUTTON_OK;
}

string16 WebsiteSettingsInfoBarDelegate::GetButtonLabel(
    InfoBarButton button) const {
  DCHECK_EQ(BUTTON_OK, button);
  return l10n_util::GetStringUTF16(IDS_WEBSITE_SETTINGS_INFOBAR_BUTTON);
}

bool WebsiteSettingsInfoBarDelegate::Accept() {
  web_contents()->GetController().Reload(true);
  return true;
}
