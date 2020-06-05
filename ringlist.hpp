#pragma once
#include <vector>

/**
* リングバッファ
*/
class RingList
{
//private:
//	std::vector<double> data;
//	const size_t reservedSize;
//
//public:
//	RingList(const size_t reservedSize)
//		: reservedSize(reservedSize)
//	{
//		data.reserve(reservedSize);
//	}
//
//	const std::vector<double>& push_back(const std::vector<int>& data)
//	{
//		const double div = 1.0 / INT_MAX;
//
//		// バッファが溢れたら，溢れた分だけ削除する
//		if (this->data.size() + data.size() > reservedSize)
//		{
//			// バッファの先頭から移動する先頭を決める
//			// 移動する先頭をバッファの先頭へコピーする
//			//std::copy(this->data.begin() + data.size(), this->data.end(), this->data.begin());
//
//			// 不要になった後端を削除する
//			//this->data.erase(this->data.end() - data.size(), this->data.end());
//		}
//
//#pragma omp simd
//		for (int i = 0; i < (int)data.size(); ++i)
//		{
//			this->data.push_back(data[i] * div);
//		}
//	}
};