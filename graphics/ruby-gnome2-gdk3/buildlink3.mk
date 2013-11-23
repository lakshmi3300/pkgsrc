# $NetBSD: buildlink3.mk,v 1.6 2013/09/02 19:50:41 adam Exp $

BUILDLINK_TREE+=	ruby-gnome2-gdk3

.if !defined(RUBY_GNOME2_GDK3_BUILDLINK3_MK)
RUBY_GNOME2_GDK3_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.ruby-gnome2-gdk3+=${RUBY_PKGPREFIX}-gnome2-gtk3>=1.2
BUILDLINK_ABI_DEPENDS.ruby-gnome2-gdk3+=${RUBY_PKGPREFIX}-gnome2-gdk3>=2.0.2nb1
BUILDLINK_PKGSRCDIR.ruby-gnome2-gdk3?=	../../graphics/ruby-gnome2-gdk3

.include "../../x11/gtk3/buildlink3.mk"
.endif # RUBY_GNOME2_GDK3_BUILDLINK3_MK

BUILDLINK_TREE+=	-ruby-gnome2-gdk3
