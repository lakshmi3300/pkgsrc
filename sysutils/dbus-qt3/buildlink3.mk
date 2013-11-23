# $NetBSD: buildlink3.mk,v 1.13 2013/06/06 12:53:52 wiz Exp $

BUILDLINK_TREE+=	dbus-qt3

.if !defined(DBUS_QT3_BUILDLINK3_MK)
DBUS_QT3_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.dbus-qt3+=	dbus-qt3>=0.70
BUILDLINK_ABI_DEPENDS.dbus-qt3+=	dbus-qt3>=0.70nb10
BUILDLINK_PKGSRCDIR.dbus-qt3?=	../../sysutils/dbus-qt3

.include "../../sysutils/dbus/buildlink3.mk"
.include "../../x11/qt3-libs/buildlink3.mk"
.endif # DBUS_QT3_BUILDLINK3_MK

BUILDLINK_TREE+=	-dbus-qt3
