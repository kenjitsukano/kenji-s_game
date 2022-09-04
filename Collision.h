#pragma once
#include"CollisionPrimitive.h"

///<summary>
///�����蔻��w���p�[�N���X
/// </summary>
class Collision
{
public:
/// <summary>
/// ���ƕ��ʂ̓����蔻��
/// </summary>
/// <param name="sphere">��</param>
/// <param name="plane">����</param>
/// <param name="inter">����(���ʏ�̍Đړ_)</param>
/// <returns>�������Ă��邩�ۂ�</returns>
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane& plane, DirectX::XMVECTOR* inter = nullptr);
/// <summary>
/// �_�ƎO�p�`�̍Őڋߓ_�����߂�
/// </summary>
/// <param name="point">�_</param>
/// <param name="triangle">�O�p�`</param>
/// <param name="closest">�Őڋߓ_(�o�͗p)</param>
	static void ClosestPtPoint2Triangle(const DirectX::XMVECTOR& point, const Triangle& triangle, DirectX::XMVECTOR* closest);
/// <summary>
/// ���Ɩ@���t���O�p�`�̓�����`�F�b�N
/// </summary>
/// <param name="sphere">��</param>
/// <param name="triangle">�O�p�`</param>
/// <param name="inter">����(�O�p�`��̍Őڋߓ_)</param>
/// <returns>�������Ă��邩�ۂ�</returns>
	static bool CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, DirectX::XMVECTOR* inter = nullptr);
/// <summary>
/// ���C�ƕ��ʂ̓����蔻��
/// </summary>
/// <param name="lay">���C</param>
/// <param name="plane">����</param>
/// <param name="inter">����(�o�͗p)</param>
/// <param name="inter">����(�o�͗p)</param>
/// <returns>�������Ă��邩�ۂ�</returns>
	static bool CheckRay2Plane(const Ray& ray, const Plane& plane, float* distance = nullptr, DirectX::XMVECTOR* inter = nullptr);
/// <summary>
/// ���C�Ɩ@���t���O�p�`�̓����蔻��
/// </summary>
/// <param name="lay">���C</param>
/// <param name="triangle">�O�p�`</param>
/// <param name="inter">����(�o�͗p)</param>
/// <param name="inter">����(�o�͗p)</param>
/// <returns>�������Ă��邩�ۂ�</returns>
	static bool CheckRay2Triangle(const Ray& ray, const Triangle& triangle, float* distance = nullptr, DirectX::XMVECTOR* inter = nullptr);

	/// <summary>
	/// ���C�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="lay">���C</param>
	/// <param name="sphere">��</param>
	/// <param name="inter">����(�o�͗p)</param>
	/// <param name="inter">����(�o�͗p)</param>
	/// <returns>�������Ă��邩�ۂ�</returns>
	static bool CheckRay2Sphere(const Ray& ray, const Sphere& sphere, float* distance = nullptr, DirectX::XMVECTOR* inter = nullptr);
private:

};

