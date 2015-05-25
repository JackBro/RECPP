﻿/*
    ██████╗ ███████╗ ██████╗██████╗ ██████╗ 
    ██╔══██╗██╔════╝██╔════╝██╔══██╗██╔══██╗
    ██████╔╝█████╗  ██║     ██████╔╝██████╔╝
    ██╔══██╗██╔══╝  ██║     ██╔═══╝ ██╔═══╝ 
    ██║  ██║███████╗╚██████╗██║     ██║     
    ╚═╝  ╚═╝╚══════╝ ╚═════╝╚═╝     ╚═╝     
* @license : <license placeholder>
*/
#include "RTTIClassHierarchyDescriptor.h"
#include "RTTIBaseClassDescriptor.h"
#include "IDAUtils.h"


char *
CRTTIClassHierarchyDescriptor::parse (
    ea_t address
) {
    if (address == BADADDR || !address) {
        return NULL;
    }

    char buffer[2048] = {0};

    msg ("0x%08.8X: RTTIClassHierarchyDescriptor\n", address);

    ea_t a = get_long (address + 4);

    IDAUtils::DwordCmt(address, "signature");
    IDAUtils::DwordCmt(address + 4, "attributes");
    IDAUtils::DwordCmt(address + 8, "numBaseClasses");
    IDAUtils::OffCmt(address + 12, "pBaseClassArray");

    a = get_long (address + 12);
    ea_t n = get_long (address + 8);
    ea_t i = 0;
    char *s = NULL;
    
    // IDAUtils::DumpNestedClass (a, indent, n);

    while (i < n) 
    {
        ea_t p = get_long (a);
        //Message(indent_str+"    BaseClass[%02d]:  %08.8Xh\n", i, p);

        asprintf (buffer, "BaseClass[%02d]", i);
        IDAUtils::OffCmt(a, buffer);
        
        if (i == 0) {
            s = CRTTIBaseClassDescriptor::parse (p);
            //??_R2A@@8 = A::`RTTI Base Class Array'
            asprintf (buffer, "??_R2%s8", &s[4]);
            IDAUtils::MakeName(a, buffer);

            //??_R3A@@8 = A::`RTTI Class Hierarchy Descriptor'
            asprintf (buffer, "??_R3%s8", &s[4]);
            IDAUtils::MakeName (address, buffer);
        }
        else {
            s = CRTTIBaseClassDescriptor::parse (p);
        }

        i++;
        a += 4;
    }

    return s;
}


char *
CRTTIClassHierarchyDescriptor::parse2 (
    ea_t address
) {
    return NULL;
}