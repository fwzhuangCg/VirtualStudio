#include "cloth.h"
#include "ClothMotion\simulation\cmcloth.h"


zfCloth::zfCloth(void) : cloth_(NULL), position_buffer_(NULL), normal_buffer_(NULL), texcoord_buffer_(NULL), vao_(NULL)
{
}

zfCloth::zfCloth(SmtClothPtr cloth) : cloth_(cloth), position_buffer_(NULL), normal_buffer_(NULL), texcoord_buffer_(NULL), vao_(NULL)
{
}

zfCloth::~zfCloth(void)
{
}

void zfCloth::cloth_init_buffer()
{
	if(!cloth_)
		return;
	
	position_buffer_ = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	position_buffer_->create();
	position_buffer_->setUsagePattern(QOpenGLBuffer::StaticDraw);

	normal_buffer_ = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	normal_buffer_->create();
	normal_buffer_->setUsagePattern(QOpenGLBuffer::StaticDraw);

	texcoord_buffer_ = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	texcoord_buffer_->create();
	texcoord_buffer_->setUsagePattern(QOpenGLBuffer::StaticDraw);

	cloth_update_buffer();
}

void zfCloth::cloth_update_buffer()
{
	if(!cloth_)
		return;

	cloth_position_buffer_.clear();
	cloth_normal_buffer_.clear();
	cloth_texcoord_buffer_.clear();

	Mesh & mesh = cloth_->mesh;
	for(auto face_it = mesh.faces.begin(); face_it != mesh.faces.end(); ++face_it)
	{
		Face * face = *face_it;
		for(int i = 0; i < 3; ++i)
		{
			for(int j = 0; j < 3; ++j)
			{
				cloth_position_buffer_.push_back(static_cast<float>(face->v[i]->node->x[j]));	
				cloth_normal_buffer_.push_back(static_cast<float>(face->v[i]->node->n[j]));
			}
			for(int j = 0; j < 2; ++j)
				cloth_texcoord_buffer_.push_back(static_cast<float>(face->v[i]->u[j]));
		}
	}
	
	position_buffer_->bind();
	position_buffer_->allocate(&cloth_position_buffer_[0], static_cast<int>(cloth_position_buffer_.size() * sizeof(float)));
	position_buffer_->release();

	normal_buffer_->bind();
	normal_buffer_->allocate(&cloth_normal_buffer_[0], static_cast<int>(cloth_normal_buffer_.size() * sizeof(float)));
	normal_buffer_->release();

	texcoord_buffer_->bind();
	texcoord_buffer_->allocate(&cloth_texcoord_buffer_[0], static_cast<int>(cloth_texcoord_buffer_.size() * sizeof(float)));
	texcoord_buffer_->release();
}

void zfCloth::initOBS(double * position, double * texcoords, int * indices, size_t faceNum) 
{
	//cloth_handler.init_avatars_to_handler(position, texcoords, indices, faceNum);
}

void zfCloth::updateOBS(double * position)
{
	//cloth_handler.update_avatars_to_handler(position);
}

void zfCloth::startSimulate()
{
	//cloth_handler.begin_simulate();
}

void zfCloth::simulateStep()
{
	//cloth_handler.sim_next_step();
}

void zfCloth::initCmFile(const char * filename, int totalFrame)
{
	//cloth_handler.init_cmfile(filename, totalFrame);
}

void zfCloth::writeToCmFile(int frame)
{
	//cloth_handler.write_frame_to_cmfile(frame);
}

void zfCloth::saveCmFile()
{
	//cloth_handler.save_cmfile();
}

void zfCloth::loadCmFile(const char * filename)
{
	//cloth_handler.load_cmfile_to_replay(filename);
	//cloth_handler.load_frame(1);
	//init_buffer();
}

size_t zfCloth::face_count() 
{ 
	return cloth_->mesh.faces.size(); 
}