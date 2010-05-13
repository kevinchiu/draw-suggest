//
// UniqueExpireLRUCache.h
//
// $Id: //poco/1.3/Foundation/include/Poco/UniqueExpireLRUCache.h#2 $
//
// Library: Foundation
// Package: Cache
// Module:  UniqueExpireLRUCache
//
// Definition of the UniqueExpireLRUCache class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef  Foundation_UniqueExpireLRUCache_INCLUDED
#define  Foundation_UniqueExpireLRUCache_INCLUDED


#include "Poco/AbstractCache.h"
#include "Poco/StrategyCollection.h"
#include "Poco/UniqueExpireStrategy.h"
#include "Poco/LRUStrategy.h"


namespace Poco {


template < 
	class TKey,
	class TValue
>
class UniqueExpireLRUCache: public AbstractCache<TKey, TValue, StrategyCollection<TKey, TValue> >
	/// A UniqueExpireLRUCache combines LRU caching and time based per entry expire caching.
	/// One can define for each cache entry a seperate timepoint
	/// but also limit the size of the cache (per default: 1024).
	/// Each TValue object must thus offer the following method:
	///    
	///    const Poco::Timestamp& getExpiration() const;
	///    
	/// which returns the absolute timepoint when the entry will be invalidated.
	/// Accessing an object will NOT update this absolute expire timepoint.
	/// You can use the Poco::ExpirationDecorator to add the getExpiration
	/// method to values that do not have a getExpiration function.
{
public:
	UniqueExpireLRUCache(long cacheSize = 1024): 
		AbstractCache<TKey, TValue, StrategyCollection<TKey, TValue> >(StrategyCollection<TKey, TValue>())
	{
		this->_strategy.pushBack(new LRUStrategy<TKey, TValue>(cacheSize));
		this->_strategy.pushBack(new UniqueExpireStrategy<TKey, TValue>());
	}

	~UniqueExpireLRUCache()
	{
	}

private:
	UniqueExpireLRUCache(const UniqueExpireLRUCache& aCache);
	UniqueExpireLRUCache& operator = (const UniqueExpireLRUCache& aCache);
};


} // namespace Poco


#endif
