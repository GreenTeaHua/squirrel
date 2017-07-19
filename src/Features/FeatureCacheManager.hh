/*
 * Copyright 2016 Alexander Richard
 *
 * This file is part of Squirrel.
 *
 * Licensed under the Academic Free License 3.0 (the "License").
 * You may not use this file except in compliance with the License.
 * You should have received a copy of the License along with Squirrel.
 * If not, see <https://opensource.org/licenses/AFL-3.0>.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */

/*
 * FeatureCacheManager.hh
 *
 *  Created on: Apr 14, 2014
 *      Author: richard
 */

#ifndef FEATURES_FEATURECACHEMANAGER_HH_
#define FEATURES_FEATURECACHEMANAGER_HH_

#include "Core/CommonHeaders.hh"
#include "FeatureReader.hh"

namespace Features {

class FeatureCachePrinter
{
public:
	FeatureCachePrinter() {}
	virtual ~FeatureCachePrinter() {}
	virtual void work();
};

}

#endif /* FEATURES_FEATURECACHEMANAGER_HH_ */
