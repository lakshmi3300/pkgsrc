# $NetBSD: buildlink3.mk,v 1.15 2013/06/06 12:53:47 wiz Exp $

BUILDLINK_TREE+=	tcl-itcl

.if !defined(TCL_ITCL_BUILDLINK3_MK)
TCL_ITCL_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.tcl-itcl+=	tcl-itcl>=3.4.1
BUILDLINK_ABI_DEPENDS.tcl-itcl?=	tcl-itcl>=3.4.1nb4
BUILDLINK_PKGSRCDIR.tcl-itcl?=	../../lang/tcl-itcl

.include "../../x11/tk/buildlink3.mk"
.endif	# TCL_ITCL_BUILDLINK3_MK

BUILDLINK_TREE+=	-tcl-itcl
