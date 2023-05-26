-- drop database if exists ppo;
-- create database ppo;
-- create database ppo_test;

drop table if exists Image cascade;
create table public.Image(
    id serial primary key,
    image_path text not null
);

drop table if exists Mark cascade;
create table public.Mark(
    id serial primary key,
    name text not null
);


drop table if exists MarkedObject cascade;
create table public.MarkedObject(
    id serial primary key,
    type int not null check (type = 0 or type = 1),
    mark_id int not null,
    image_id int not null
);

drop table if exists Coord cascade;
create table public.Coord(
    id serial primary key,
    marked_object_id int not null,
    x_coord int not null,
    y_coord int not null
);

drop table if exists Users cascade;
create table public.Users(
    id serial primary key,
    login varchar(15) not null,
    password text not null,
    privilege_lvl int not null
);


alter table Coord add foreign key (marked_object_id) references public.MarkedObject(id) on delete cascade ;
alter table MarkedObject add foreign key (mark_id) references public.Mark(id);
alter table MarkedObject add foreign key (image_id) references public.Image(id);

