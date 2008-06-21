/*MT*
    
    MediaTomb - http://www.mediatomb.cc/
    
    weborama_service.h - this file is part of MediaTomb.
    
    Copyright (C) 2005 Gena Batyan <bgeradz@mediatomb.cc>,
                       Sergey 'Jin' Bostandzhyan <jin@mediatomb.cc>
    
    Copyright (C) 2006-2008 Gena Batyan <bgeradz@mediatomb.cc>,
                            Sergey 'Jin' Bostandzhyan <jin@mediatomb.cc>,
                            Leonhard Wimmer <leo@mediatomb.cc>
    
    MediaTomb is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 2
    as published by the Free Software Foundation.
    
    MediaTomb is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    version 2 along with MediaTomb; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
    
    $Id: weborama_service.h 1811 2008-05-14 16:48:32Z jin_eld $
*/

/// \file weborama_service.h
/// \brief Definition of the WeboramaService class.

#ifdef WEBORAMA

#ifndef __WEBORAMA_SERVICE_H__
#define __WEBORAMA_SERVICE_H__

#include "zmm/zmm.h"
#include "mxml/mxml.h"
#include "online_service.h"
#include "url.h"
#include "dictionary.h"
#include <curl/curl.h>


typedef enum
{
    WR_mood_dull_lively = 0,
    WR_mood_lively,
    WR_mood_active_lively,
    WR_mood_dull,
    WR_mood_neutral,
    WR_mood_active,
    WR_mood_dull_sad,
    WR_mood_sad,
    WR_mood_sad_active,
} wr_mood_t;

/// \brief This is an interface for all online services, the function
/// handles adding/refreshing content in the database.
class WeboramaService : public OnlineService
{
public:
    WeboramaService();
    ~WeboramaService();
    /// \brief Retrieves user specified content from the service and adds
    /// the items to the database.
    virtual bool refreshServiceData(zmm::Ref<Layout> layout);

    /// \brief Get the type of the service (i.e. Weborama, Shoutcast, etc.)
    virtual service_type_t getServiceType();

    /// \brief Get the human readable name for the service
    virtual zmm::String getServiceName();

    /// \brief Parse the xml fragment from the configuration and gather
    /// the user settings in a service task structure.
    virtual zmm::Ref<zmm::Object> defineServiceTask(zmm::Ref<mxml::Element> xmlopt, zmm::Ref<zmm::Object> params);

protected:
    // the handle *must never be used from multiple threads*
    CURL *curl_handle;
    // safeguard to ensure the above
    pthread_t pid;

    // url retriever class
    zmm::Ref<URL> url;

    /// \brief This function will retrieve the XML according to the parametrs
    zmm::Ref<mxml::Element> getData(zmm::Ref<Dictionary> params);

    /// \brief task that we will be working with when refreshServiceData is
    /// called.
    int current_task;

    class WeboramaTask : public zmm::Object
    {
    public:
        WeboramaTask();
        /// \brief Weborama API URL parameters
        zmm::Ref<Dictionary> parameters;

        /// \brief Amount of items that we are allowed to get.
        int amount;

        /// \brief Amount of items that have been fetched.
        int amount_fetched;

        /// \brief Starting index of the item to fetch
        int start_index;

        /// \brief Starging index as specified in the configuration by the user
        int cfg_start_index;
    };


};

#endif//__ONLINE_SERVICE_H__

#endif//WEBORAMA