# $NetBSD: buildlink3.mk,v 1.40 2013/07/05 13:29:36 ryoon Exp $

BUILDLINK_TREE+=	libkipi

.if !defined(LIBKIPI_BUILDLINK3_MK)
LIBKIPI_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libkipi+=	libkipi>=4.8.0
BUILDLINK_ABI_DEPENDS.libkipi?=	libkipi>=4.10.3nb4
BUILDLINK_PKGSRCDIR.libkipi?=	../../graphics/libkipi

.include "../../x11/kdelibs4/buildlink3.mk"
.endif	# LIBKIPI_BUILDLINK3_MK

BUILDLINK_TREE+=	-libkipi
