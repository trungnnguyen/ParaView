/*=========================================================================

   Program: ParaView
   Module:  pqActiveThreeSliceRenderViewOptions.cxx

   Copyright (c) 2005-2008 Sandia Corporation, Kitware Inc.
   All rights reserved.

   ParaView is a free software; you can redistribute it and/or modify it
   under the terms of the ParaView license version 1.2.

   See License_v1.2.txt for the full ParaView license.
   A copy of this license can be obtained by contacting
   Kitware Inc.
   28 Corporate Drive
   Clifton Park, NY 12065
   USA

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/

/// \file pqActiveThreeSliceRenderViewOptions.cxx
/// \date 8/02/2012

#include "pqActiveThreeSliceRenderViewOptions.h"

#include <QPointer>

#include "pqRenderViewOptions.h"
#include "pqOptionsDialog.h"
#include "pqThreeSliceViewOptions.h"

class pqActiveThreeSliceRenderViewOptions::pqInternal
{
public:
  QPointer<pqOptionsDialog> Dialog;
  pqRenderViewOptions* GeneralOptions;
  pqThreeSliceViewOptions* Options;
};

pqActiveThreeSliceRenderViewOptions::pqActiveThreeSliceRenderViewOptions(QObject *parentObject)
  : pqActiveViewOptions(parentObject)
{
  this->Internal = new pqInternal;
}

pqActiveThreeSliceRenderViewOptions::~pqActiveThreeSliceRenderViewOptions()
{
  delete this->Internal;
}

void pqActiveThreeSliceRenderViewOptions::showOptions(
    pqView *view, const QString &page, QWidget *widgetParent)
{
  if(!this->Internal->Dialog)
    {
    this->Internal->Dialog = new pqOptionsDialog(widgetParent);
    this->Internal->Dialog->setApplyNeeded(true);
    this->Internal->Dialog->setObjectName("ActiveRenderViewOptions");
    this->Internal->Dialog->setWindowTitle("View Settings (Render View)");
    this->Internal->GeneralOptions = new pqRenderViewOptions;
    this->Internal->Options = new pqThreeSliceViewOptions;
    this->Internal->Dialog->addOptions(this->Internal->GeneralOptions);
    this->Internal->Dialog->addOptions(this->Internal->Options);
    if(page.isEmpty())
      {
      QStringList pages = this->Internal->GeneralOptions->getPageList();
      pages.append(this->Internal->Options->getPageList());
      if(pages.size())
        {
        this->Internal->Dialog->setCurrentPage(pages[0]);
        }
      }
    else
      {
      this->Internal->Dialog->setCurrentPage(page);
      }

    this->connect(this->Internal->Dialog, SIGNAL(finished(int)),
        this, SLOT(finishDialog()));
    }

  this->changeView(view);
  this->Internal->Dialog->show();
}

void pqActiveThreeSliceRenderViewOptions::changeView(pqView *view)
{
  this->Internal->GeneralOptions->setView(view);
  this->Internal->Options->setView(view);
}

void pqActiveThreeSliceRenderViewOptions::closeOptions()
{
  if(this->Internal->Dialog)
    {
    this->Internal->Dialog->accept();
    }
}

void pqActiveThreeSliceRenderViewOptions::finishDialog()
{
  emit this->optionsClosed(this);
}


