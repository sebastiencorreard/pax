import uuid
from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select
from sqlalchemy.orm import selectinload

from db import get_db
from models.class_model import Class, ClassStudent
from models.user import User
from sqlalchemy.orm import aliased
from api.schemas.class_schema import ClassCreate, ClassResponse, ClassDetailResponse, UserBrief, StudentClassResponse
from api.deps import get_current_user, require_role

router = APIRouter(prefix="/api/classes", tags=["classes"])


def _check_ownership(cls: Class, current_user: User) -> None:
    if cls.teacher_id != current_user.id and current_user.role != "admin":
        raise HTTPException(status_code=403, detail="Classe appartenant à un autre enseignant")


@router.get("/mine", response_model=list[StudentClassResponse])
async def list_my_classes(
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("student")),
):
    Teacher = aliased(User)
    result = await db.execute(
        select(Class, Teacher)
        .join(ClassStudent, ClassStudent.class_id == Class.id)
        .join(Teacher, Teacher.id == Class.teacher_id)
        .where(ClassStudent.student_id == current_user.id)
        .order_by(Class.name)
    )
    return [
        StudentClassResponse(
            id=cls.id,
            name=cls.name,
            teacher_first_name=teacher.first_name,
            teacher_last_name=teacher.last_name,
        )
        for cls, teacher in result.all()
    ]


@router.get("/", response_model=list[ClassResponse])
async def list_classes(
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    if current_user.role == "admin":
        q = select(Class)
    else:
        q = select(Class).where(Class.teacher_id == current_user.id)
    result = await db.execute(q.order_by(Class.created_at.desc()).options(selectinload(Class.students)))
    classes = result.scalars().all()
    out = []
    for cls in classes:
        out.append(ClassResponse(
            id=cls.id,
            name=cls.name,
            teacher_id=cls.teacher_id,
            created_at=cls.created_at,
            student_count=len(cls.students),
        ))
    return out


@router.post("/", response_model=ClassResponse, status_code=201)
async def create_class(
    data: ClassCreate,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    cls = Class(name=data.name, teacher_id=current_user.id)
    db.add(cls)
    await db.commit()
    await db.refresh(cls)
    return ClassResponse(id=cls.id, name=cls.name, teacher_id=cls.teacher_id, created_at=cls.created_at, student_count=0)


@router.get("/{class_id}", response_model=ClassDetailResponse)
async def get_class(
    class_id: int,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    result = await db.execute(
        select(Class).where(Class.id == class_id)
        .options(selectinload(Class.students).selectinload(ClassStudent.student))
    )
    cls = result.scalar_one_or_none()
    if not cls:
        raise HTTPException(status_code=404, detail="Classe introuvable")
    _check_ownership(cls, current_user)
    students = [UserBrief.model_validate(cs.student) for cs in cls.students]
    return ClassDetailResponse(
        id=cls.id, name=cls.name, teacher_id=cls.teacher_id,
        created_at=cls.created_at, students=students
    )


@router.delete("/{class_id}", status_code=204)
async def delete_class(
    class_id: int,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    result = await db.execute(select(Class).where(Class.id == class_id))
    cls = result.scalar_one_or_none()
    if not cls:
        raise HTTPException(status_code=404, detail="Classe introuvable")
    _check_ownership(cls, current_user)
    await db.delete(cls)
    await db.commit()


@router.post("/{class_id}/students", status_code=201)
async def add_student(
    class_id: int,
    body: dict,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    student_id_str = body.get("student_id")
    if not student_id_str:
        raise HTTPException(status_code=422, detail="student_id requis")
    try:
        student_uuid = uuid.UUID(str(student_id_str))
    except ValueError:
        raise HTTPException(status_code=422, detail="student_id invalide")

    result = await db.execute(select(Class).where(Class.id == class_id))
    cls = result.scalar_one_or_none()
    if not cls:
        raise HTTPException(status_code=404, detail="Classe introuvable")
    _check_ownership(cls, current_user)

    result = await db.execute(select(User).where(User.id == student_uuid))
    student = result.scalar_one_or_none()
    if not student or student.role != "student":
        raise HTTPException(status_code=404, detail="Élève introuvable")

    existing = await db.execute(
        select(ClassStudent).where(
            ClassStudent.class_id == class_id,
            ClassStudent.student_id == student_uuid,
        )
    )
    if existing.scalar_one_or_none():
        return {"status": "already_member"}

    db.add(ClassStudent(class_id=class_id, student_id=student_uuid))
    await db.commit()
    return {"status": "ok"}


@router.delete("/{class_id}/students/{student_id}", status_code=204)
async def remove_student(
    class_id: int,
    student_id: uuid.UUID,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    result = await db.execute(select(Class).where(Class.id == class_id))
    cls = result.scalar_one_or_none()
    if not cls:
        raise HTTPException(status_code=404, detail="Classe introuvable")
    _check_ownership(cls, current_user)

    result = await db.execute(
        select(ClassStudent).where(
            ClassStudent.class_id == class_id,
            ClassStudent.student_id == student_id,
        )
    )
    link = result.scalar_one_or_none()
    if not link:
        raise HTTPException(status_code=404, detail="Élève non trouvé dans cette classe")
    await db.delete(link)
    await db.commit()
