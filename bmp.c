/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:40:24 by labintei          #+#    #+#             */
/*   Updated: 2021/04/28 14:27:41 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"map.h"


void		bmp_save_file(struct s_env *env)
{

	open("cube3d.bmp",O_CREAT ,S_IXOTH);

_______________________________________________________________________________
	FILE TYPE DATA
	
	informations about bmp files
	14 bytes
	5 fields

	filetype
	unsigned char	ft[2];
	ft[0] = 'B';
	ft[1] = 'M';
	/* BID specifie le filetype au BID*/
	filesize(nombres de pixels)
	unsigned int	size;
	size = env->l.r[0] * env->l.r[1];
	/*  1 bytes = 1 pixels*/
	RESERVED
	unsigned int r;
	r = 0;
	RESERVED
	unsigned int rbis;
	rbis  = 0;

	pixeldataoffset
	unsigned int offset;
	offset = 0;
	/* pixel pointe au debut du fichier*/

_______________________________________________________________________________

	IMAGE IMFORMATIONS DATA
	
	bmpinfoheader
	40 bytes
	11 fields

	Header size /* NOMBRE DE BYTES DANS HEADER */
	unsigned int sh;
	sh = 40;

	Image width
	int		iw;
	iw = env->l.r[0];

	Image height
	int		ih;
	ih = env->l.r[1];

	Plane/* Nomber of color plane*/
	unsigned int p;
	p = 1;

	bits per pixels
	unsigned int bpp;
	bpp = 32;

	compression
	unsigned int comp;
	comp = 0;

	image size 	/* NO COMP USE -> 0*/
	unsigned int isize;
	isize  = 0;

	Xpixelpermeter
	int	xpix;
	xpix = 0
	(no preference)

	Ypixelpermeter
	int	ypix;
	ypix = 0;
	(no preference)

	Totalcolor
	unsigned int	color; 
	color = n;
	/* 0 en decimal correspond a 2 bits par pixel*/
	/* NOMBRE DE COULEURS UTILISES*/

	Important COLOR
	unsigned int	impcolor;
	imp = 0;

________________________________________________________________________________

	COLOR PALLET

	Bits per PIXEL

	1	black_white
	4	16 colors
	8	(2^8)colors
	16	(2^16)RGB
	24	(2^24)RGB
	32	(2^32)RGBA channel de (8 bits pour la transparence)



________________________________________________________________________________
	RAW PIXEL DATA
	
	

	return ;
}