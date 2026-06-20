#******************************************************************************
#FILE:               doc/Makefile
#LANGUAGE:           make
#SYSTEM:             POSIX
#DESCRIPTION
#   Build the documentation from org-mode sources into several formats:
#     .html  (browse)        via emacs ox-html
#     .info  (browse, Emacs) via emacs ox-texinfo + makeinfo
#     .pdf   (read)          via emacs ox-texinfo + texi2pdf
#     .N     (man page)      via pandoc
#
#   This build is OPTIONAL and separate from the library build: it needs
#   emacs (batch), texinfo (makeinfo), a TeX install (texi2pdf), and pandoc.
#
#       make            # build all formats
#       make html info pdf man
#       make install PREFIX=/usr/local
#       make clean
#AUTHORS
#   <PJB> Pascal J. Bourguignon
#LEGAL
#   GPL.  Copyright Pascal J. Bourguignon 2026.
#******************************************************************************

EMACS    ?= emacs
MAKEINFO ?= makeinfo
TEXI2PDF ?= texi2pdf
PANDOC   ?= pandoc
INSTALL  ?= install
PREFIX   ?= /usr/local

ORG  := $(wildcard *.org)
HTML := $(ORG:.org=.html)
TEXI := $(ORG:.org=.texi)
INFO := $(ORG:.org=.info)
PDF  := $(ORG:.org=.pdf)
MAN  := $(ORG:.org=.7)

EMACS_BATCH = $(EMACS) -Q --batch

DOCDIR  = $(PREFIX)/share/doc/common
INFODIR = $(PREFIX)/share/info
MANDIR  = $(PREFIX)/share/man/man7

.PHONY: all html info pdf man clean install
all: html info pdf man
html: $(HTML)
info: $(INFO)
pdf:  $(PDF)
man:  $(MAN)

%.html: %.org
	$(EMACS_BATCH) --visit $< --eval '(require (quote ox-html))' \
		-f org-html-export-to-html

%.texi: %.org
	$(EMACS_BATCH) --visit $< --eval '(require (quote ox-texinfo))' \
		-f org-texinfo-export-to-texinfo

%.info: %.texi
	$(MAKEINFO) --no-split -o $@ $<

%.pdf: %.texi
	$(TEXI2PDF) --batch --quiet -o $@ $< >/dev/null 2>&1

%.7: %.org
	$(PANDOC) --standalone --from org --to man -o $@ $<

install: all
	$(INSTALL) -d $(DOCDIR) $(INFODIR) $(MANDIR)
	$(INSTALL) -m 644 $(HTML) $(PDF) $(DOCDIR)/
	$(INSTALL) -m 644 $(INFO) $(INFODIR)/
	-install-info --info-dir=$(INFODIR) $(INFO)
	$(INSTALL) -m 644 $(MAN) $(MANDIR)/

clean:
	rm -f $(HTML) $(TEXI) $(INFO) $(PDF) $(MAN) \
	      *.aux *.cp *.cps *.fn *.ky *.log *.pg *.toc *.tp *.vr *.vrs *.fns

#### doc/Makefile ####
