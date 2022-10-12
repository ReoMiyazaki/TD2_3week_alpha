#include "Player.h"

using namespace MathUtility;

void Player::Initialize(float moveCircleRadius, Vector2 moveCircle)
{
	debugText_ = DebugText::GetInstance();
	input_ = Input::GetInstance();
	model_ = Model::Create();
	input_ = Input::GetInstance();

	player_.Initialize();
	playerRad = 0;

	// �v���C���[�̍s���~
	for (int i = 0; i < 64; i++)
	{
		playerMoveLine[i].Initialize();
		float rad = 360.0f / 64.0f * i;
		moveCircle.x = sin(PI / 180 * rad) * moveCircleRadius;
		moveCircle.y = cos(PI / 180 * rad) * moveCircleRadius;
		Vector3 pos;
		pos.x = moveCircle.x;
		pos.z = moveCircle.y;
		pos.y = 0;
		playerMoveLine[i].translation_ = pos;
		playerMoveLine[i].scale_ = { 0.1f,0.1f,0.1f };
		playerMoveLine[i].MatUpdate();
	}
}

void Player::Update(float moveCircleRadius)
{
	// �X�e�[�g���A�C�h���Ȃ�
	if (state == PlayerState::Idle)
	{
		// �v���C���[�����_�𒆐S�ɉ�]
		playerRad += 2.0f;
		playerRad = fmodf(playerRad, 360.0f);
		rotation = player_.rotation_;
		rotation.y += playerRad;
		player_.rotation_.y = playerRad * PI / 180.0f;
		player_.rotation_.z -= 0.25f;
		player_.rotation_.z = fmodf(player_.rotation_.z, 360.0f);

		movePos.x = sin(PI / 180 * playerRad) * moveCircleRadius;
		movePos.z = cos(PI / 180 * playerRad) * moveCircleRadius;
		player_.translation_ = movePos;

		// �X�y�[�X�L�[�̃g���K�[�Ń`���[�W��ԂɈڍs
		if (input_->TriggerKey(DIK_SPACE))
		{
			state = PlayerState::Charge;
			player_.rotation_.z = 0.0f;

		}

	}
	//else if (state == PlayerState::Charge) {
	//	//�`���[�W�X�e�[�g���̓W�����v�͂𗭂߂Ȃ��牡�ɉ�]
	//	if (jumpPower <= 5.5f)// ����
	//	{
	//		jumpPower += 0.1f;
	//	}
	//	else if (jumpPower > 5.5f)// �����W�����v
	//	{
	//		state = PlayerState::Jump;
	//	}

	// player�`���[�W����
	else if (state == PlayerState::Charge)
	{
		// �`���[�W�X�e�[�g���̓W�����v�͂𗭂߂Ȃ��牡�ɉ�]
		jumpPower += 0.1f;
		player_.rotation_.y += jumpPower / 10.0f;

		// �X�y�[�X�L�[�������ꂽ��W�����v��ԂɈڍs
		if (!input_->PushKey(DIK_SPACE)) {
			state = PlayerState::Jump;
		}
	}

	// player�W�����v����
	else if (state == PlayerState::Jump)
	{
		// �`���[�W���ꂽ�W�����v�͂ŃW�����v
		player_.translation_.y += jumpPower;
		jumpPower--;
		// ������0�ȉ��ɂȂ�����A�C�h���ɖ߂�
		if (player_.translation_.y <= 0) {
			player_.translation_.y = 0;
			jumpPower = 0;
			state = PlayerState::Idle;
		}
		// �g���K�[�Ń_�b�V���ړ�
		if (input_->TriggerKey(DIK_SPACE))
		{
			state = PlayerState::dash;
			player_.rotation_.y = 0.0f;
			//���@�ʒu����180�x��]�����ʒu���ړ�����W�ɐݒ�
			afterPos.x = sin(PI / 180 * (180 + playerRad)) * moveCircleRadius;
			afterPos.y = player_.translation_.y;
			afterPos.z = cos(PI / 180 * (180 + playerRad)) * moveCircleRadius;
			playerPosition = GetWorldPosition();
			//�ړ�����W�ƌ����W����ړ��p���x�x�N�g���v�Z
			dashSpeed.x = afterPos.x - player_.translation_.x;
			dashSpeed.z = afterPos.z - player_.translation_.z;
			//���x���ړ����Ԃŕ���
			dashSpeed.x /= static_cast<float>(dashTime);
			dashSpeed.z /= static_cast<float>(dashTime);

			player_.rotation_.y = playerRad * PI / 180.0f;
		}
	}

	// player�_�b�V������
	else if (state == PlayerState::dash)
	{
		/*Vector3Length(distance);
		Vector3Normalize(distance);*/

	//	dashSpeed *= kMoveSpeed;
		//�ړ����x�̉��Z
		player_.translation_.x += dashSpeed.x;
		player_.translation_.z += dashSpeed.z;

		player_.rotation_.z += 0.5f;

		//���@�̕��s�ړ��ʂ��X�y�[�X�L�[�������ɐݒ肵���ړ�����W�Ȃ�ړ��I���B�����t�F�[�Y��
		if(static_cast<int>(player_.translation_.x) ==static_cast<int>(afterPos.x) &&
			static_cast<int>(player_.translation_.y) == static_cast<int>(afterPos.y) &&
			static_cast<int>(player_.translation_.z) == static_cast<int>(afterPos.z)){
			player_.translation_ = afterPos;
			player_.rotation_.x = 0.0f;
			state = PlayerState::Jump;
			jumpPower = 0.0f;
		}

		/*if (player_.translation_.x >= afterPos.x && player_.translation_.z >= afterPos.z ||
			player_.translation_.x >= afterPos.x && afterPos.z >= player_.translation_.z ||
			afterPos.x >= player_.translation_.x && player_.translation_.z >= afterPos.z ||
			afterPos.x >= player_.translation_.x && afterPos.z >= player_.translation_.z) {
			dashSpeed = { 0,0,0 };
			player_.translation_.x = afterPos.x;
			player_.translation_.z = afterPos.z;
			player_.translation_.y--;
		}
		if (player_.translation_.y < 0) {
			jumpPower = 0.0f;
			player_.translation_.y = 0;
			state = PlayerState::Idle;
		}*/

	}

	player_.MatUpdate();
}

void Player::Draw(ViewProjection viewProjection_)
{
	model_->Draw(player_, viewProjection_);

	for (int i = 0; i < 64; i++)
	{
		model_->Draw(playerMoveLine[i], viewProjection_);
	}
	// �f�o�b�O�t�H���g
	debugText_->Printf("playerRad:%f", playerRad);
	debugText_->SetPos(50, 70);
	debugText_->Printf("state:%d(0:Idle,1:Charge,2:Jump)", state);
	debugText_->SetPos(50, 90);
	debugText_->Printf("jumpPower:%f", jumpPower);
	debugText_->SetPos(50, 110);
	debugText_->Printf("afterPos:(%f,%f,%f)", afterPos.x, afterPos.y, afterPos.z);
	debugText_->SetPos(50, 130);
	debugText_->Printf("dashSpeed:(%f,%f,%f)", dashSpeed.x, dashSpeed.y, dashSpeed.z);
	debugText_->SetPos(50, 150);
	debugText_->Printf("playerTransform:(%f,%f,%f)", player_.translation_.x, player_.translation_.y, player_.translation_.z);
	debugText_->SetPos(50, 170);
	debugText_->Printf("rotation_:(%f,%f,%f)", player_.rotation_.x, player_.rotation_.y, player_.rotation_.z);
}

Vector3 Player::GetWorldPosition()
{
	//���[���h���W�����邽�߂̕ϐ�
	Vector3 worldPos;

	//���[���h�s��̕��s�ړ��������擾
	worldPos.x = player_.matWorld_.m[3][0];
	worldPos.y = player_.matWorld_.m[3][1];
	worldPos.z = player_.matWorld_.m[3][2];

	return worldPos;
}
