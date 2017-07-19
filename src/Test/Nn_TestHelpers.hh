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
 * Nn_TestHelpers.hh
 *
 *  Created on: Jun 3, 2014
 *      Author: richard
 */

#ifndef TEST_NN_TESTHELPERS_HH_
#define TEST_NN_TESTHELPERS_HH_

#include <Nn/NeuralNetwork.hh>

Nn::NeuralNetwork* configureFeedForwardNetwork();
void modifyFeedForwardNetwork(Nn::NeuralNetwork* network);

Nn::NeuralNetwork* configureRecurrentNetwork();
void modifyRecurrentNetwork(Nn::NeuralNetwork* network);

#endif /* TEST_NN_TESTHELPERS_HH_ */
