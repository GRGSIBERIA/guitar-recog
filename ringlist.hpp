#pragma once
#include <vector>

/**
* �����O�o�b�t�@
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
//		// �o�b�t�@����ꂽ��C��ꂽ�������폜����
//		if (this->data.size() + data.size() > reservedSize)
//		{
//			// �o�b�t�@�̐擪����ړ�����擪�����߂�
//			// �ړ�����擪���o�b�t�@�̐擪�փR�s�[����
//			//std::copy(this->data.begin() + data.size(), this->data.end(), this->data.begin());
//
//			// �s�v�ɂȂ�����[���폜����
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