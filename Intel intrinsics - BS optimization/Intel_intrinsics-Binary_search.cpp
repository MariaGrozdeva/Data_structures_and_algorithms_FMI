#include <iostream>
#include <immintrin.h>

/*
* @param hayStack - the input data that will be searched in
* @param needles  - the values that will be searched
* @param indices  - the indices of the needles (or -1 if the needle is not found)
*/
static void AVXBinarySearch(const int* hayStack, std::size_t hayStackCount, const int* needles, std::size_t needlesCount, int* indices)
{
	const int needlesPerIteration = 8;

	__m256i onesVector = _mm256_set1_epi32(1);
	__m256i minusOnesVector = _mm256_set1_epi32(-1);

	for (size_t i = 0; i < needlesCount; i += needlesPerIteration)
	{
		__m256i indexVector = minusOnesVector;
		__m256i needleVector = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(needles + i));

		__m256i leftVector = _mm256_setzero_si256();
		__m256i rightVector = _mm256_set1_epi32(hayStackCount - 1);
		if (hayStack[0] == hayStack[hayStackCount - 1])
			rightVector = leftVector;

		__m256i leftGtRightVector = _mm256_setzero_si256();

		while (_mm256_movemask_epi8(leftGtRightVector) != -1)
		{
			leftGtRightVector = _mm256_cmpgt_epi32(leftVector, rightVector);
			__m256i leftNotGtRightVector = _mm256_andnot_si256(leftGtRightVector, minusOnesVector);

			// mid = left + (right - left) / 2
			__m256i midPositionVector = _mm256_add_epi32(leftVector,
				_mm256_srli_epi32(_mm256_sub_epi32(rightVector, leftVector), 1));
			__m256i midElementVector = _mm256_i32gather_epi32(hayStack, midPositionVector, sizeof(int));

			__m256i equalVector = _mm256_cmpeq_epi32(needleVector, midElementVector);
			__m256i greaterVector = _mm256_cmpgt_epi32(needleVector, midElementVector);
			__m256i smallerOrEqualVector = _mm256_andnot_si256(greaterVector, minusOnesVector);

			indexVector = _mm256_blendv_epi8(indexVector, midPositionVector, equalVector);
			leftVector = _mm256_blendv_epi8(leftVector, _mm256_add_epi32(midPositionVector, onesVector),
				_mm256_and_si256(greaterVector, leftNotGtRightVector));
			rightVector = _mm256_blendv_epi8(rightVector, _mm256_sub_epi32(midPositionVector, onesVector),
				_mm256_and_si256(smallerOrEqualVector, leftNotGtRightVector));
		}
		_mm256_storeu_si256(reinterpret_cast<__m256i*>(indices + i), indexVector);
	}
}

int main()
{
	
}