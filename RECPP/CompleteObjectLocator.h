﻿/*
    ██████╗ ███████╗ ██████╗██████╗ ██████╗ 
    ██╔══██╗██╔════╝██╔════╝██╔══██╗██╔══██╗
    ██████╔╝█████╗  ██║     ██████╔╝██████╔╝
    ██╔══██╗██╔══╝  ██║     ██╔═══╝ ██╔═══╝ 
    ██║  ██║███████╗╚██████╗██║     ██║     
    ╚═╝  ╚═╝╚══════╝ ╚═════╝╚═╝     ╚═╝     
* @license : <license placeholder>
*/
#pragma once

// ---------- Includes ------------
#include "RECPP.h"
#include "RTTIClassHierarchyDescriptor.h"

// ---------- Defines -------------


// ------ Class declaration -------
class CompleteObjectLocator {
    public:

    uint32 signature; // Always zero ?
    uint32 offset;    // Offset of this vtable in the class ?
    uint32 cdOffset;  // No idea
    struct _TypeDescriptor *pTypeDescriptor; // TypeDescriptor of the class
    struct _RTTIClassHierarchyDescriptor *pClassDescriptor; //inheritance hierarchy
    
    /* 
     * @brief : Check if the current address is a valid CompleteObjectLocator
     * @param address : The address to check for a CompleteObjectLocator
     * @return true if valid, false otherwise
     */
    static bool 
    isValid (
        ea_t address
    );

    /* 
     * @brief : Parse the COL at address
     * @param address : The address to parse for a CompleteObjectLocator
     * @return true if valid, false otherwise
     */
    static void
    parse (
        ea_t address
    );

    
    static char *
    get_type_name_by_col (
        ea_t colAddress,
        char *buffer,
        size_t bufferSize
    );
};

